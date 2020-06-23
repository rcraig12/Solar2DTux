ProjectName            := template_arm
OutDir                 := Solar2DSimulator
OutputFile             := $(OutDir)/$(ProjectName)
PreprocessorSwitch     := -D
Preprocessors          := $(PreprocessorSwitch)Rtt_LUA_COMPILER $(PreprocessorSwitch)LUA_DL_DLOPEN $(PreprocessorSwitch)wxUSE_MEDIACTRL=1 $(PreprocessorSwitch)wxUSE_WEBVIEW=1 $(PreprocessorSwitch)__WXGTK__ $(PreprocessorSwitch)HAVE_SSIZE_T $(PreprocessorSwitch)wxUSE_XTEST $(PreprocessorSwitch)wxHAS_INOTIFY $(PreprocessorSwitch)wxUSE_SELECT_DISPATCHER $(PreprocessorSwitch)wxUSE_LIBMSPACK $(PreprocessorSwitch)WXWIN_COMPATIBILITY_3_0 $(PreprocessorSwitch)wxUSE_TASKBARBUTTON $(PreprocessorSwitch)wxUSE_DBGHELP $(PreprocessorSwitch)wxUSE_WINRT $(PreprocessorSwitch)wxUSE_PRIVATE_FONTS $(PreprocessorSwitch)wxUSE_ACTIVITYINDICATOR $(PreprocessorSwitch)wxUSE_ADDREMOVECTRL $(PreprocessorSwitch)wxUSE_UNSAFE_WXSTRING_CONV $(PreprocessorSwitch)wxUSE_STD_CONTAINERS_COMPATIBLY $(PreprocessorSwitch)wxUSE_SECRETSTORE $(PreprocessorSwitch)wxUSE_GLCANVAS $(PreprocessorSwitch)_DEBUG $(PreprocessorSwitch)Rtt_LINUX_ENV $(PreprocessorSwitch)Rtt_EXPORT= $(PreprocessorSwitch)FT2_BUILD_LIBRARY $(PreprocessorSwitch)ALMIXER_COMPILE_WITHOUT_SDL $(PreprocessorSwitch)SOUND_SUPPORTS_WAV $(PreprocessorSwitch)SOUND_SUPPORTS_MPG123 $(PreprocessorSwitch)SOUND_SUPPORTS_OGG $(PreprocessorSwitch)LINUX_LIB $(PreprocessorSwitch)OPT_GENERIC $(PreprocessorSwitch)HAVE_STRERROR $(PreprocessorSwitch)NO_REAL $(PreprocessorSwitch)ENABLE_ALMIXER_THREADS 
CXXFLAGS               := -O2 -g3 -std=c++11 -Wfatal-errors -Wno-narrowing $(Preprocessors)
CFLAGS                 := -O2 -g3 -Wall $(Preprocessors)

export

all: 
	@echo "----------Building project:[ linux_rtt ]----------"
	@"$(MAKE)" -f "linux_rtt.mk" PreBuild && "$(MAKE)" -j4 -f "linux_rtt.mk" && "$(MAKE)" -f "linux_rtt.mk" PostBuild
	cd $(OutDir) && tar -czf $(ProjectName).tgz $(ProjectName) && rm -rf $(ProjectName) && cd ..
	mv $(OutDir)/$(ProjectName).tgz $(OutDir)/Resources

clean:
	rm -f $(OutDir)/Resources/$(ProjectName).tgz
	rm -f $(OutDir)/Resources/
	@"$(MAKE)" -f "linux_rtt.mk" clean	
