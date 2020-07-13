##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Solar2DConsole
ConfigurationName      :=Debug
WorkspacePath          :=/home/robert/Solar2DTux/platform/linux
ProjectPath            :=/home/robert/Solar2DTux/platform/linux
IntermediateDirectory  :=./Console
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Robert
Date                   :=13/07/20
CodeLitePath           :=/home/robert/.codelite
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=Solar2DSimulator/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)__WX__ 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Solar2DConsole.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  $(shell wx-config   --libs --unicode=yes)
IncludePath            :=  $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -std=c++11 -Wall $(shell wx-config --cxxflags --unicode=yes  ) $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(shell wx-config --cxxflags --unicode=yes  ) $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/Rtt_LinuxConsoleApp.cpp$(ObjectSuffix) $(IntermediateDirectory)/Rtt_LinuxConsole.cpp$(ObjectSuffix) $(IntermediateDirectory)/Rtt_LinuxIPCServerConnection.cpp$(ObjectSuffix) $(IntermediateDirectory)/Rtt_LinuxIPCConnectionBase.cpp$(ObjectSuffix) $(IntermediateDirectory)/Rtt_LinuxIPCServer.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Console || $(MakeDirCommand) ./Console


$(IntermediateDirectory)/.d:
	@test -d ./Console || $(MakeDirCommand) ./Console

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/Rtt_LinuxConsoleApp.cpp$(ObjectSuffix): Rtt_LinuxConsoleApp.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Rtt_LinuxConsoleApp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Rtt_LinuxConsoleApp.cpp$(DependSuffix) -MM Rtt_LinuxConsoleApp.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robert/Solar2DTux/platform/linux/Rtt_LinuxConsoleApp.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Rtt_LinuxConsoleApp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Rtt_LinuxConsoleApp.cpp$(PreprocessSuffix): Rtt_LinuxConsoleApp.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Rtt_LinuxConsoleApp.cpp$(PreprocessSuffix) Rtt_LinuxConsoleApp.cpp

$(IntermediateDirectory)/Rtt_LinuxConsole.cpp$(ObjectSuffix): Rtt_LinuxConsole.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Rtt_LinuxConsole.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Rtt_LinuxConsole.cpp$(DependSuffix) -MM Rtt_LinuxConsole.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robert/Solar2DTux/platform/linux/Rtt_LinuxConsole.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Rtt_LinuxConsole.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Rtt_LinuxConsole.cpp$(PreprocessSuffix): Rtt_LinuxConsole.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Rtt_LinuxConsole.cpp$(PreprocessSuffix) Rtt_LinuxConsole.cpp

$(IntermediateDirectory)/Rtt_LinuxIPCServerConnection.cpp$(ObjectSuffix): Rtt_LinuxIPCServerConnection.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Rtt_LinuxIPCServerConnection.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Rtt_LinuxIPCServerConnection.cpp$(DependSuffix) -MM Rtt_LinuxIPCServerConnection.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robert/Solar2DTux/platform/linux/Rtt_LinuxIPCServerConnection.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Rtt_LinuxIPCServerConnection.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Rtt_LinuxIPCServerConnection.cpp$(PreprocessSuffix): Rtt_LinuxIPCServerConnection.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Rtt_LinuxIPCServerConnection.cpp$(PreprocessSuffix) Rtt_LinuxIPCServerConnection.cpp

$(IntermediateDirectory)/Rtt_LinuxIPCConnectionBase.cpp$(ObjectSuffix): Rtt_LinuxIPCConnectionBase.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Rtt_LinuxIPCConnectionBase.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Rtt_LinuxIPCConnectionBase.cpp$(DependSuffix) -MM Rtt_LinuxIPCConnectionBase.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robert/Solar2DTux/platform/linux/Rtt_LinuxIPCConnectionBase.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Rtt_LinuxIPCConnectionBase.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Rtt_LinuxIPCConnectionBase.cpp$(PreprocessSuffix): Rtt_LinuxIPCConnectionBase.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Rtt_LinuxIPCConnectionBase.cpp$(PreprocessSuffix) Rtt_LinuxIPCConnectionBase.cpp

$(IntermediateDirectory)/Rtt_LinuxIPCServer.cpp$(ObjectSuffix): Rtt_LinuxIPCServer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Rtt_LinuxIPCServer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Rtt_LinuxIPCServer.cpp$(DependSuffix) -MM Rtt_LinuxIPCServer.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robert/Solar2DTux/platform/linux/Rtt_LinuxIPCServer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Rtt_LinuxIPCServer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Rtt_LinuxIPCServer.cpp$(PreprocessSuffix): Rtt_LinuxIPCServer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Rtt_LinuxIPCServer.cpp$(PreprocessSuffix) Rtt_LinuxIPCServer.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Console/


