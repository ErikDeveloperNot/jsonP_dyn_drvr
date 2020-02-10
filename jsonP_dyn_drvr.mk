##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=jsonP_dyn_drvr
ConfigurationName      :=Debug
WorkspacePath          :=/Users/user1/udemy/CPP/UdemyCPP
ProjectPath            :=/Users/user1/udemy/CPP/UdemyCPP/jsonP_dyn_drvr
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=User One
Date                   :=09/02/2020
CodeLitePath           :="/Users/user1/Library/Application Support/CodeLite"
LinkerName             :=/usr/bin/clang++
SharedObjectLinkerName :=/usr/bin/clang++ -dynamiclib -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="jsonP_dyn_drvr.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)/Users/user1/udemy/CPP/UdemyCPP/jsonP_dyn $(IncludeSwitch)/Users/user1/Git/sajson/include $(IncludeSwitch)/Users/user1/Git/SimpleJSON/src $(IncludeSwitch)/Users/user1/Git/cJSON $(IncludeSwitch)/Users/user1/Git/rapidjson/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)jsonP_dyn 
ArLibs                 :=  "jsonP_dyn" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/Users/user1/udemy/CPP/UdemyCPP/jsonP_dyn/Debug 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/clang++
CC       := /usr/bin/clang
CXXFLAGS :=  -g -O3 -std=c++11 $(Preprocessors)
CFLAGS   :=  -g -O3 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/Applications/codelite.app/Contents/SharedSupport/
Objects0=$(IntermediateDirectory)/main_all.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/JSON.cpp$(ObjectSuffix) $(IntermediateDirectory)/net_chunk_impl.cpp$(ObjectSuffix) $(IntermediateDirectory)/JSONValue.cpp$(ObjectSuffix) $(IntermediateDirectory)/cJSON.c$(ObjectSuffix) 



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
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main_all.cpp$(ObjectSuffix): main_all.cpp $(IntermediateDirectory)/main_all.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/user1/udemy/CPP/UdemyCPP/jsonP_dyn_drvr/main_all.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main_all.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main_all.cpp$(DependSuffix): main_all.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main_all.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main_all.cpp$(DependSuffix) -MM main_all.cpp

$(IntermediateDirectory)/main_all.cpp$(PreprocessSuffix): main_all.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main_all.cpp$(PreprocessSuffix) main_all.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/user1/udemy/CPP/UdemyCPP/jsonP_dyn_drvr/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/JSON.cpp$(ObjectSuffix): JSON.cpp $(IntermediateDirectory)/JSON.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/user1/udemy/CPP/UdemyCPP/jsonP_dyn_drvr/JSON.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/JSON.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/JSON.cpp$(DependSuffix): JSON.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/JSON.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/JSON.cpp$(DependSuffix) -MM JSON.cpp

$(IntermediateDirectory)/JSON.cpp$(PreprocessSuffix): JSON.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/JSON.cpp$(PreprocessSuffix) JSON.cpp

$(IntermediateDirectory)/net_chunk_impl.cpp$(ObjectSuffix): net_chunk_impl.cpp $(IntermediateDirectory)/net_chunk_impl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/user1/udemy/CPP/UdemyCPP/jsonP_dyn_drvr/net_chunk_impl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/net_chunk_impl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/net_chunk_impl.cpp$(DependSuffix): net_chunk_impl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/net_chunk_impl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/net_chunk_impl.cpp$(DependSuffix) -MM net_chunk_impl.cpp

$(IntermediateDirectory)/net_chunk_impl.cpp$(PreprocessSuffix): net_chunk_impl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/net_chunk_impl.cpp$(PreprocessSuffix) net_chunk_impl.cpp

$(IntermediateDirectory)/JSONValue.cpp$(ObjectSuffix): JSONValue.cpp $(IntermediateDirectory)/JSONValue.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/Users/user1/udemy/CPP/UdemyCPP/jsonP_dyn_drvr/JSONValue.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/JSONValue.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/JSONValue.cpp$(DependSuffix): JSONValue.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/JSONValue.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/JSONValue.cpp$(DependSuffix) -MM JSONValue.cpp

$(IntermediateDirectory)/JSONValue.cpp$(PreprocessSuffix): JSONValue.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/JSONValue.cpp$(PreprocessSuffix) JSONValue.cpp

$(IntermediateDirectory)/cJSON.c$(ObjectSuffix): cJSON.c $(IntermediateDirectory)/cJSON.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/Users/user1/udemy/CPP/UdemyCPP/jsonP_dyn_drvr/cJSON.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cJSON.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cJSON.c$(DependSuffix): cJSON.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cJSON.c$(ObjectSuffix) -MF$(IntermediateDirectory)/cJSON.c$(DependSuffix) -MM cJSON.c

$(IntermediateDirectory)/cJSON.c$(PreprocessSuffix): cJSON.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cJSON.c$(PreprocessSuffix) cJSON.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


