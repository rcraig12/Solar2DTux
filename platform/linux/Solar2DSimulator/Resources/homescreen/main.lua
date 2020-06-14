------------------------------------------------------------------------------
--
-- This file is part of the Corona game engine.
-- For overview and more information on licensing please refer to README.md 
-- Home page: https://github.com/coronalabs/corona
-- Contact: support@coronalabs.com
--
------------------------------------------------------------------------------
local widget = require("widget")
local simErr, simulator = pcall(require, "simulator")
if not simErr then
	simulator = require "simulator_stub"
end
local json = require("json")
local lfs = require("lfs")
local sFormat = string.format
local recentProjectsPath = sFormat("%s/.Solar2D/Sandbox/Simulator/Documents/recents.json", os.getenv("HOME")) 
local backgroundColor = {37 / 255, 37 / 255, 38 / 255, 1}
local buttonBackgroundColor = {51 / 255, 51 / 255, 55 / 255, 1}
local mainFont = "OpenSans-Regular.ttf"
local lightFont = "OpenSans-Light.ttf"
local buttonYOffset = 50

display.setDefault("background", backgroundColor[1], backgroundColor[2], backgroundColor[3])

local function scriptPath()
	local str = debug.getinfo(2, "S").source:sub(2):match("(.*/)")
	return str:match("(.*/)")
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

local function getAppName(str)
	local lastPathComponent = getLastPathComponent(str)
	return (lastPathComponent:sub(2, lastPathComponent:len() - 1))
end

local function getProjectPath(str)
	local pathIndexes = {}

	for i = 1, #str do
		if (str:sub(i, i) == "/") then
			pathIndexes[#pathIndexes + 1] = i
		end
	end

	return string.sub(str, 1, pathIndexes[#pathIndexes])
end

local function loadTable(path)
	local loc = location

	if not location then
		loc = defaultLocation
	end

	local file, errorString = io.open(path, "r")

	if not file then
		return {}
	else
		local contents = file:read("*a")
		local t = json.decode(contents)
		io.close(file)

		return t
	end
end

local function saveTable(t, path)
	local loc = location

	if not location then
		loc = defaultLocation
	end

	local file, errorString = io.open(path, "w")

	if not file then
		print("File error: " .. errorString)
		return false
	else
		file:write(json.encode(t))
		io.close(file)

		return true
	end
end

local function removeExistingProjectFromRecents(recentProjects, projectName)
	-- see if this project already exists in recent projects
	if (#recentProjects > 0) then
		local existingPosition = 0

		for i = 1, #recentProjects do
			if (recentProjects[i].formattedString == projectName) then
				existingPosition = i
				break;
			end
		end

		if (existingPosition > 0) then
			table.remove(recentProjects, existingPosition)
			saveTable(recentProjects, recentProjectsPath)
		end

		if (#recentProjects > 7) then
			for i = 7, #recentProjects do
				table.remove(recentProjects, i)
			end

			saveTable(recentProjects, recentProjectsPath)
		end
	end
end

local solar2DTuxLogo = display.newImageRect("images/logo.png", 600, 200)
solar2DTuxLogo.anchorX = 0
solar2DTuxLogo.anchorY = 0
solar2DTuxLogo.x = 20
solar2DTuxLogo.y = 10

local latestNewsTitle = display.newText(
{
	text = "Latest News:",
	font = mainFont,
	fontSize = 24,
	align = "left"
})
latestNewsTitle.anchorX = 1
latestNewsTitle.anchorY = 0
latestNewsTitle.x = display.contentWidth - 180
latestNewsTitle.y = 20
latestNewsTitle:setFillColor(1, 1, 1, 1)

local latestNewsText = display.newText(
{
	text = "Version 0.1-RC is in development.\nWe're hard at work developing the\nlatest version of Solar2DTux.\n\nStay tuned for more info!",
	font = lightFont,
	fontSize = 20,
	align = "left"
})
latestNewsText.anchorX = 1
latestNewsText.anchorY = 0
latestNewsText.x = display.contentWidth - 20
latestNewsText.y = latestNewsTitle.y + 30
latestNewsText:setFillColor(1, 1, 1, 1)

-- get started
local getStartedText = display.newText(
{
	text = "Get Started",
	font = mainFont,
	fontSize = 24,
	align = "left"
})
getStartedText.anchorX = 0
getStartedText.anchorY = 0
getStartedText.x = 20
getStartedText.y = 220
getStartedText:setFillColor(1, 1, 1, 1)

local separatorLine = display.newRect(0, 0, display.contentWidth - 20, 1)
separatorLine.anchorY = 0
separatorLine.x = display.contentCenterX
separatorLine.y = getStartedText.y + 30
separatorLine:setFillColor(unpack(buttonBackgroundColor))

local function createButton(label, onRelease)
	local button = widget.newButton(
	{
		label = label,
		emboss = false,
		shape = "roundedRect",
		width = 200,
		height = 40,
		cornerRadius = 2,
		fillColor = 
		{ 
			default = buttonBackgroundColor, 
			over = {buttonBackgroundColor[1], buttonBackgroundColor[2], buttonBackgroundColor[3], 0.7}, 
		},
		labelColor = 
		{
			default = {1, 1, 1, 1},
			over = {1, 1, 1, 0.7}
		},
		onRelease = onRelease
	})

	return button
end

local cloneProjectButton = createButton("Clone A Repository", 
	function(event) 
		simulator.show("clone")
	end
)
cloneProjectButton.anchorX = 0
cloneProjectButton.x = 20
cloneProjectButton.y = getStartedText.y + 60

local openProjectButton = createButton("Open Existing Project",
	function(event)
		local recentProjects = loadTable(recentProjectsPath)
		simulator.show("open")
			
		local projectPath = simulator.getCurrentProjectPath()
		local projectName = getAppName(projectPath)
		local projectDir = projectPath

		-- see if this project already exists in recent projects
		removeExistingProjectFromRecents(recentProjects, projectName)
		table.insert(recentProjects, 1, {formattedString = projectName, fullURLString = projectDir})
		saveTable(recentProjects, recentProjectsPath)
	end
)
openProjectButton.anchorX = 0
openProjectButton.x = 20
openProjectButton.y = cloneProjectButton.y + buttonYOffset

local createProjectButton = createButton("Create New Project",
	function(event)
		simulator.show("new")
	end
)
createProjectButton.anchorX = 0
createProjectButton.x = 20
createProjectButton.y = openProjectButton.y + buttonYOffset

local openSampleCodeButton = createButton("View Sample Code",
	function(event)
		simulator.show("sampleCode")
	end
)
openSampleCodeButton.anchorX = 0
openSampleCodeButton.x = 20
openSampleCodeButton.y = createProjectButton.y + buttonYOffset

local reportAnIssueButton = createButton("Report An Issue",
	function(event)
		system.openURL("https://github.com/DannyGlover/Solar2DTux/issues")
	end
)
reportAnIssueButton.anchorX = 0
reportAnIssueButton.x = 20
reportAnIssueButton.y = openSampleCodeButton.y + buttonYOffset

-- helpful links
local helpfulLinksText = display.newText(
{
	text = "Helpful Links",
	font = mainFont,
	fontSize = 24,
	align = "left"
})
helpfulLinksText.anchorX = 1
helpfulLinksText.anchorY = 0
helpfulLinksText.x = display.contentWidth - 80
helpfulLinksText.y = getStartedText.y
helpfulLinksText:setFillColor(1, 1, 1, 1)

local documentationButton = createButton("Documentation", 
	function(event) 
		system.openURL("https://docs.coronalabs.com/api") 
	end
)
documentationButton.anchorX = 1
documentationButton.x = display.contentWidth - 20
documentationButton.y = helpfulLinksText.y + 60

local githubButton = createButton("GitHub", 
	function(event) 
		system.openURL("https://github.com/DannyGlover/Solar2DTux") 
	end
)
githubButton.anchorX = 1
githubButton.x = display.contentWidth - 20
githubButton.y = documentationButton.y + buttonYOffset

local forumsButton = createButton("Forums",
	function(event) 
		system.openURL("https://forums.solar2d.com/") 
	end
)
forumsButton.anchorX = 1
forumsButton.x = display.contentWidth - 20
forumsButton.y = githubButton.y + buttonYOffset

local pluginsButton = createButton("Plugins",
	function(event) 
		system.openURL("https://plugins.solar2d.com/") 
	end
)
pluginsButton.anchorX = 1
pluginsButton.x = display.contentWidth - 20
pluginsButton.y = forumsButton.y + buttonYOffset

local patreonButton = createButton("Patreon",
	function(event) 
		system.openURL("https://patreon.com/dannyglover") 
	end
)
patreonButton.anchorX = 1
patreonButton.x = display.contentWidth - 20
patreonButton.y = pluginsButton.y + buttonYOffset

-- recent projects
local recentProjectsText = display.newText(
{
	text = "Recent Projects",
	font = mainFont,
	fontSize = 24,
	align = "left"
})
recentProjectsText.anchorX = 0.5
recentProjectsText.anchorY = 0
recentProjectsText.x = display.contentCenterX - 10
recentProjectsText.y = getStartedText.y
recentProjectsText:setFillColor(1, 1, 1, 1)

local recentProjects = loadTable(recentProjectsPath)

if (#recentProjects > 0) then
	local function openRecentProject(event)
		local details = event.target.details
		local recentProjects = loadTable(recentProjectsPath)
		removeExistingProjectFromRecents(recentProjects, details.formattedString)
		table.insert(recentProjects, 1, {formattedString = details.formattedString, fullURLString = details.fullURL})
		saveTable(recentProjects, recentProjectsPath)

		simulator.show("open", details.fullURL)
	end

	for i = 1, #recentProjects do
		local icon = nil
		local projectName = recentProjects[i].formattedString
		local projectDir = getProjectPath(recentProjects[i].fullURLString)
		projectDir = projectDir:sub(1, projectDir:len() -1)
		local projectIconFile = simulator.getPreference("welcomeScreenIconFile") or "Icon.png"
		local projectIcon = sFormat("%s/%s", projectDir, projectIconFile)

		if (lfs.attributes(projectIcon) ~= nil) then
			simulator.setProjectResourceDirectory(projectDir .. "/")
			icon = display.newImageRect(projectIconFile, system.ResourceDirectory, 40, 40)
			icon.anchorX = 0
			icon.anchorY = 0
			icon.x = getStartedText.x + getStartedText.contentWidth + 180
			icon.y = i == 1 and recentProjectsText.y + 50 or recentProjectsText.y + (50 * i)
		end

		local projectNameText = display.newText(
		{
			text = projectName,
			fontSize = 18,
			font = mainFont,
			align = "left"
		})
		projectNameText.anchorX = 0
		projectNameText.anchorY = 0
		projectNameText.x = icon.x + icon.contentWidth + 15
		projectNameText.y = icon.y
		projectNameText.details = {formattedString = projectName, fullURL = sFormat("%s/main.lua", projectDir)}
		projectNameText:addEventListener("tap", openRecentProject)

		-- limit long paths
		if (projectDir:len() > 70) then
			projectDir = sFormat("..%s", projectDir:sub(projectDir:len() - 70, projectDir:len()))
		end

		local projectPathText = display.newText(
		{
			text = projectDir,
			fontSize = 14,
			font = lightFont,
			align = "left"
		})
		projectPathText.anchorX = 0
		projectPathText.anchorY = 0
		projectPathText.x = projectNameText.x
		projectPathText.y = projectNameText.y + 20
	end
else
	local noRecentProjectsText = display.newText(
	{
		text = "No recent projects were found. Why not create one?",
		font = mainFont,
		fontSize = 18,
		align = "left"
	})
	noRecentProjectsText.anchorX = 0
	noRecentProjectsText.anchorY = 0
	noRecentProjectsText.x = getStartedText.x + getStartedText.contentWidth + 180
	noRecentProjectsText.y = recentProjectsText.y + 40
	noRecentProjectsText:setFillColor(1, 1, 1, 1)
end

local versionText = display.newText(
{
	text = "Solar2DTux Version: 0.1-RC",
	font = lightFont,
	fontSize = 18,
	align = "left"
})
versionText.anchorX = 0
versionText.anchorY = 1
versionText.x = 20
versionText.y = display.contentHeight - 10

local copyrightText = display.newText(
{
	text = "Copyright 2020 © Solar2D / Solar2DTux",
	font = lightFont,
	fontSize = 18,
	align = "left"
})
copyrightText.anchorX = 1
copyrightText.anchorY = 1
copyrightText.x = display.contentWidth - 20
copyrightText.y = display.contentHeight - 10

local function onResize(event)
	print(">>>>> WINDOW RESIZED FROM LUA")
end

Runtime:addEventListener("resize", onResize)