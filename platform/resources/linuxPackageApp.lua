------------------------------------------------------------------------------
--
-- This file is part of the Corona game engine.
-- For overview and more information on licensing please refer to README.md 
-- Home page: https://github.com/coronalabs/corona
-- Contact: support@coronalabs.com
--
------------------------------------------------------------------------------

processExecute = processExecute or os.execute

local lfs = require("lfs")
local json = require("json")
local http = require("socket.http")
local debugBuildProcess = 0
local dirSeparator = package.config:sub(1,1)
local buildSettings = nil
local sFormat = string.format

local function fileExists(name)
	local f = io.open(name, "r")

	if (f ~= nil) then
		io.close(f) return true
	else 
		return false 
	end
end

-- check if /usr/bin/tar exists, it is in Mac but not in Linux
local tar = "/usr/bin/tar"

if (fileExists(tar) == false) then
	tar = "tar"   -- for linux
end

local function log(...)
	myprint(...)
end

local function log3(...)
	if (debugBuildProcess >= 3) then
		myprint(...)
	end
end

local function quoteString(str)
	str = str:gsub('\\', '\\\\')
	str = str:gsub('"', '\\"')

	return sFormat("\"%s\"", str)
end

local function dirExists(path)
    local cd = lfs.currentdir()
	local is = lfs.chdir(path) and true or false

	lfs.chdir(cd)
	
    return is
end

local function globToPattern(g)
	local p = "^"  -- pattern being built
	local i = 0    -- index in g
	local c        -- char at index i in g.

	-- unescape glob char
	local function unescape()
		if (c == '\\') then
			i = i + 1; c = g:sub(i,i)
			
			if (c == '') then
				p = '[^]'
				return false
			end
		end
		
		return true
	end

	-- escape pattern char
	local function escape(c)
		return c:match("^%w$") and c or '%' .. c
	end

	-- Convert tokens at end of charset.
	local function charsetEnd()
		while 1 do
			if (c == '') then
				p = '[^]'
				return false
			elseif (c == ']') then
				p = p .. ']'
				break
			else
				if (not unescape()) then 
					break 
				end
				
				local c1 = c
				i = i + 1; c = g:sub(i,i)
				
				if (c == '') then
					p = '[^]'
					return false
				elseif (c == '-') then
					i = i + 1; c = g:sub(i,i)
					
					if (c == '') then
						p = '[^]'
						return false
					elseif (c == ']') then
						p = p .. escape(c1) .. '%-]'
						break
					else
						if (not unescape()) then 
							break 
						end
					
						p = p .. escape(c1) .. '-' .. escape(c)
					end
				elseif (c == ']') then
					p = p .. escape(c1) .. ']'
					break
				else
					p = p .. escape(c1)
					i = i - 1 -- put back
				end
			end
			
			i = i + 1; c = g:sub(i,i)
		end
		
		return true
	end

	-- Convert tokens in charset.
	local function charset()
		i = i + 1; c = g:sub(i,i)
		
		if (c == '' or c == ']') then
			p = '[^]'
			return false
		elseif (c == '^' or c == '!') then
			i = i + 1; c = g:sub(i,i)
			
			if (c == ']') then
				-- ignored
			else
				p = p .. '[^'

				if (not charsetEnd()) then 
					return false 
				end
			end
		else
			p = p .. '['

			if (not charsetEnd()) then 
				return false 
			end
		end

		return true
	end

	-- Convert tokens
	while 1 do
		i = i + 1; c = g:sub(i,i)
		
		if (c == '') then
			p = p .. '$'
			break
		elseif (c == '?') then
			p = p .. '.'
		elseif (c == '*') then
			p = p .. '.*'
		elseif (c == '[') then
			if (not charset()) then 
				break 
			end
		elseif (c == '\\') then
			i = i + 1; c = g:sub(i,i)
			
			if (c == '') then
				p = p .. '\\$'
				break
			end
		
			p = p .. escape(c)
		else
			p = p .. escape(c)
		end
	end
	
	return p
end

local function pathJoin(p1, p2, ... )
	local res
	local p1s = p1:sub(-1) == dirSeparator
	local p2s = p2:sub(1, 1) == dirSeparator
	
	if (p1s and p2s) then
		res = p1:sub(1,-2) .. p2
	elseif (p1s or p2s) then
		res = p1 .. p2
	else
		res = p1 .. dirSeparator .. p2
	end
	
	if ... then
		return pathJoin(res, ...)
	else
		return res
	end
end

local function extractTar(archive, dst)
	lfs.mkdir(dst)
	local cmd = tar .. ' -xzf ' .. quoteString(archive) .. ' -C ' ..  quoteString(dst .. "/") 
	log('extractTar: ' .. cmd)
	
	return os.execute(cmd)
end

local function gzip(path, appname, ext, destFile)
	local dst = pathJoin(path, destFile)
	local src = ''
	
	for i = 1, #ext do	
		src = src .. appname .. ext[i]
		src = src .. ' '
	end
	
	local cmd = 'cd '.. quoteString(path) .. ' && /usr/bin/zip "' .. dst .. '" ' .. src
	log3('gzip', cmd)
	os.execute(cmd)

	for i = 1, #ext do	
		os.remove(pathJoin(path, appname .. ext[i]))
	end
end

local function zip(folder, zipfile)
	local cmd = 'cd '.. folder .. ' && /usr/bin/zip -r -X ' .. zipfile .. ' ' .. '*'
	log3('zip:', cmd)
	
	return os.execute(cmd)
end

local function unzip(archive, dst)
	local cmd = '/usr/bin/unzip -o -q ' .. quoteString(archive) .. ' -d ' ..  quoteString(dst)
	log3('inzip:', cmd)
	
	return os.execute(cmd)
end

local function createTarGZ(srcDir, tarFile, tarGZFile)
	log('crerating', tarGZFile)

	local cmd = 'cd '.. quoteString(srcDir) .. ' && ' .. tar .. ' --exclude=' .. tarGZFile .. ' -czf ' .. tarGZFile .. ' .'
	log3('createTarGZ:', cmd)
	
	return os.execute(cmd)
end

local function setControlParams(args, localTmpDir)
	local path = pathJoin(localTmpDir, 'DEBIAN', 'control')
	local f = io.open(path, "rb")
	
	if (f) then
		local s = f:read("*a")
		io.close(f)

		local count
 		s, count = s:gsub('@package', args.applicationName, 1)
 		s, count = s:gsub('@version', args.versionName, 1)
 		s, count = s:gsub('@size', '10000', 1)		-- fixme
 		s, count = s:gsub('@maintainer', 'Corona Labs corp. <support@coronalabs.com>', 1)
 		s, count = s:gsub('@description', 'This is my app', 1)
 		s = s .. '  ' .. 'description1\n'
 		s = s .. '  ' .. 'description2\n'
 		s = s .. '  ' .. 'description3\n'

		f = io.open(path, "wb")

		if (f) then
			f:write(s)
			io.close(f)
		end
	end
end

-- create deb file
local function createDebArchive(debFile, srcDir)
	local fi = io.open(pathJoin(srcDir, debFile), "wb")
	
	if (fi) then
		fi:write('!<arch>\n')
		fi:write('debian-binary   1410122664  0     0     100644  4         `\n')
		fi:write('2.0\n')

		-- add control.tar.gz
		local path = pathJoin(srcDir, 'DEBIAN', 'control.tar.gz')
		local f = io.open(path, "rb")
		
		if (f) then
			local filesize = f:seek("end")
			local s = sFormat('%d', filesize)
			
			while s:len() < 10 do
				s = s .. ' '
			end
			
			fi:write('control.tar.gz  1410122664  0     0     100644  ' .. s .. '`\n')
			f:seek("set", 0)

			local buf = f:read("*a")
			fi:write(buf)

			if ((filesize % 2) ~= 0) then
				fi:write('\n')
			end

			f:close()
		end

		-- add data.tar.gz
		local path = pathJoin(srcDir, 'CONTENTS', 'data.tar.gz')
		local f = io.open(path, "rb")
		
		if (f) then
			local filesize = f:seek("end")
			local s = sFormat('%d', filesize)
			
			while s:len() < 10 do
				s = s .. ' '
			end
			
			fi:write('data.tar.gz     1410122664  0     0     100644  ' .. s .. '`\n')
			f:seek("set", 0)
	
			local buf = f:read("*a")
			fi:write(buf)

			if (filesize % 2) ~= 0 then
				fi:write('\n')
			end

			f:close()
		end

		fi:close()
	end
end

local function copyFile(src, dst)
	local fi = io.open(src, "rb")
	
	if (fi) then
		local buf = fi:read("*a")
		fi:close()
		fi = io.open(dst, "wb")

		if (fi) then
			fi:write(buf)
			fi:close()
			return true
		end

		log3('copyFile failed to write: ', src, dst)
		return false
	end

	log3('copyFile failed to read: ', src, dst)
	return false;
end

local function copyDir(src, dst)
	local cmd = 'cp -R ' .. quoteString(src) .. '/. ' ..  quoteString(dst)
	log3('copydir:', cmd)

	return os.execute(cmd)
end

local function removeDir(dir)
	local cmd = "rm -f -r " .. quoteString(dir)
	log3('removeDir:', cmd)

	os.execute(cmd)
end

local function linuxDownloadPlugins(buildRevision, tmpDir, pluginDstDir)
	if (type(buildSettings) ~= 'table') then
		-- no build.settings file, so no plugins to download
		return nil
	end

	local collectorParams = 
	{ 
		pluginPlatform = 'linux',
		plugins = buildSettings.plugins or {},
		destinationDirectory = tmpDir,
		build = buildRevision,
		extractLocation = pluginDstDir,
	}
	
	print("package path: ", package.path)
	local pluginCollector = require "CoronaBuilderPluginCollector"

	return pluginCollector.collect(collectorParams)
end


local function getExcludePredecate()
	local excludes = 
	{
		"*.config",
		"*.lu*",
		"**/*lu*",
		"*.bak",
		"*.orig",
		"*.swp",
		"*.DS_Store",
		"*.apk",
		"*.obb",
		"*.obj",
		"*.o",
		"*.lnk",
		"*.class",
		"*.log",
		"*.xcassets",
		"*.storyboardc",
		".*",
		"*.properties",
		"*.settings",
		"**AndroidResources",
		"**res",
		"*Icon*.png",
	}

	-- append 'all:' and 'linux:'
	if (buildSettings and buildSettings.excludeFiles) then
		if (buildSettings.excludeFiles.all) then
			-- append excludes from 'all:'
			local excl = buildSettings.excludeFiles.all

			for i = 1, #excl do	
				excludes[#excludes + 1] = excl[i]
			end
		end

		if (buildSettings.excludeFiles.linux) then
			-- append excludes from 'linux:'
			local excl = buildSettings.excludeFiles.linux

			for i = 1, #excl do	
				excludes[#excludes + 1] = excl[i]
			end
		end
	end

	-- glob ==> regexp
	for i = 1, #excludes do
		excludes[i] = globToPattern(excludes[i])
	end

	return function(fileName)
		for i = 1, #excludes do
			local rc = fileName:match(excludes[i])
			
			if (rc ~= nil) then
				return true
			end
		end
	
		return false
	end
end

local function deleteUnusedFiles(srcDir, excludePredicate)
	local paths = {srcDir}
	local count = 0
	local dirCount = 0
	local fileList = {}
	local directoryList = {}

	local function scanFoldersRecursively(event)
		if (#paths == 0) then
			paths = nil
			
			for i = 1, #fileList do
				local file = fileList[i]

				if (excludePredicate(file)) then
					local result, reason = os.remove(file)

					if (result) then
						log('removed file at  ' .. file)
					else
						log("! couldn't remove file at " .. file) 
					end
				end
			end

			for i = 1, #directoryList do
				local dir = directoryList[i]
				
				if (excludePredicate(dir)) then
					log("removing directory: " ..  dir)
					os.execute(sFormat('rm -rf "%s"', dir))
				end
			end

			fileList = nil
			directoryList = nil

			return
		end

		local fullPath = nil
		local attributes = nil

		for file in lfs.dir(paths[1]) do
			if (file ~= "." and file ~= "..") then
				fullPath = sFormat("%s/%s", paths[1], file)
				attributes = lfs.attributes(fullPath)

				if (attributes) then
					if (attributes.mode == "directory") then
						--print("file: " .. file .. " is directory")
						table.insert(paths, fullPath)
						dirCount = dirCount + 1
						directoryList[dirCount] = fullPath
					elseif (attributes.mode == "file") then
						count = count + 1
						fileList[count] = fullPath
					end
				end
			end
		end

		table.remove(paths, 1)
		scanFoldersRecursively()
	end

	scanFoldersRecursively()
end

local function getPathFromString(str)
	local pathIndexes = {}

	for i = 1, #str do
		if (str:sub(i, i) == "/") then
			pathIndexes[#pathIndexes + 1] = i
		end
	end

	return string.sub(str, 1, pathIndexes[#pathIndexes])
end

local function getLastPathComponent(str)
	local pathIndexes = {}

	for i = 1, #str do
		if (str:sub(i, i) == "/") then
			pathIndexes[#pathIndexes + 1] = i
		end
	end

	return string.sub(str, pathIndexes[#pathIndexes - 1], pathIndexes[#pathIndexes])
end

local function makeApp(arch, linuxappFolder, template, args, templateName)
	-- sanity check
	local archivesize = lfs.attributes(template, "size")

	if (archivesize == nil or archivesize == 0) then
		return sFormat('failed to open template: %s', template)
	end

	local ret = extractTar(template, linuxappFolder)

	if (ret ~= 0) then
		return sFormat('failed to unpack template %s to %s - error: %s', template, linuxappFolder, ret)
	end

	log(sFormat('unzipped %s to %s', template, linuxappFolder))

	-- copy binary
	local binaryPath = sFormat("%s/%s", linuxappFolder, "linuxTemplate")
	log(sFormat("renaming binary from %s to %s/%s", linuxappFolder, linuxappFolder, args.applicationName))
	os.rename(binaryPath, sFormat("%s/%s", linuxappFolder , args.applicationName))

	-- dowmload plugins
	local pluginDownloadDir = pathJoin(args.tmpDir, "pluginDownloadDir")
	local pluginExtractDir = pathJoin(args.tmpDir, "pluginExtractDir")
	local binPlugnDir = pathJoin(pluginExtractDir, arch)
	local luaPluginDir = pathJoin(pluginExtractDir, 'lua', 'lua_51')

	if (dirExists(luaPluginDir)) then
		copyDir(luaPluginDir, pluginExtractDir)
	end
	
	if (dirExists(binPlugnDir)) then
		copyDir(binPlugnDir, linuxappFolder)
		copyDir(binPlugnDir, linuxappFolder)
	end
	
	-- gather files into appFolder
	ret = copyDir(args.srcDir, linuxappFolder)

	if (ret ~= 0) then
		return sFormat("failed to copy %s to %s", args.srcDir, linuxappFolder)
	end

	log(sFormat("copied app files from %s to %s", args.srcDir, linuxappFolder))

	-- copy standard resources
	local widgetsDir = pathJoin(getPathFromString(template), 'Corona')

	if (args.useStandardResources) then
		ret = copyDir(widgetsDir, pathJoin(linuxappFolder, "Resources"))

		if (ret ~= 0) then
			return "failed to copy widget resources"
		end

		log("copied widget resources")
	end

	-- compile .lua
	local rc = compileScriptsAndMakeCAR(args.linuxParams, linuxappFolder, linuxappFolder, linuxappFolder)

	if (not rc) then
		return "Failed to create resource.car file"
	end

	lfs.mkdir(pathJoin(linuxappFolder, "Resources"))
	os.rename(pathJoin(linuxappFolder, "resource.car"), pathJoin(linuxappFolder, "Resources", "resource.car"))
	log("created resource.car file")

	-- delete unused files
	deleteUnusedFiles(linuxappFolder, getExcludePredecate())
end

-- global script to call from C++
function linuxPackageApp(args)
	debugBuildProcess = args.debugBuildProcess
	log('linux builder started')
	log3(json.prettify(args))

	log("template location: ", getPathFromString(args.templateLocation))
	log("template: " .. getLastPathComponent(args.templateLocation))

	local template = args.templateLocation
	local templateArm = template
	templateArm = templateArm:gsub('linuxTemplate.tgz', 'armTemplate.tgz')

	-- read settings
	local buildSettingsFile = pathJoin(args.srcDir, 'build.settings')
	local oldSettings = _G['settings']
	_G['settings'] = nil
	pcall( function() dofile(buildSettingsFile) end	)
	buildSettings = _G['settings']
	_G['settings'] = oldSettings

	local success = false;

	-- create app folder
	local linuxappFolder = pathJoin(args.dstDir, args.applicationName)

	os.execute(sFormat('rm -rf "%s"', linuxappFolder))

	local success = lfs.mkdir(linuxappFolder)
	if (not success) then
		return sFormat('Failed to create app folder: %s', linuxappFolder)
	end

	log(sFormat('Created app folder: %s', linuxappFolder))

	local pluginDownloadDir = pathJoin(args.tmpDir, "pluginDownloadDir")
	local pluginExtractDir = pathJoin(args.tmpDir, "pluginExtractDir")
	lfs.mkdir(pluginDownloadDir)
	lfs.mkdir(pluginExtractDir)

	local msg = linuxDownloadPlugins(args.buildRevision, pluginDownloadDir, pluginExtractDir)

	if (type(msg) == 'string') then
		return msg
	end

	log("template name " .. getLastPathComponent(template))

	local rc = makeApp('x86-64', linuxappFolder, template, args, getLastPathComponent(template))

	if (rc ~= nil) then
		return rc
	end

	log('Linux build finished')

	return nil 
end
