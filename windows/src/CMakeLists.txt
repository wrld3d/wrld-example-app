set(headers ${headers} src
)
set(currsources
  src/AppHost.cpp
  src/AppHost.h
  src/AppInputDelegate.cpp
  src/AppInputDelegate.h
  src/AppRunner.cpp
  src/AppRunner.h
  src/ExampleAppPch.h
  src/GlDisplayService.cpp
  src/GlDisplayService.h
  src/main.cpp
  src/main.h
)

set(precompiled_header_clr_result WindowsClrPch_$(Configuration)_$(Platform).pch)
set(clr_compile_flags "/clr /EHa /Fp${precompiled_header_clr_result}")

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set_source_files_properties(src/ExampleAppPch.cpp PROPERTIES COMPILE_FLAGS "/Yc /Fp${precompiled_header_result}")
set(currsources ${currsources} src/ExampleAppPch.cpp)

set_source_files_properties(src/ExampleAppClrPch.cpp PROPERTIES COMPILE_FLAGS "/Yc /clr /EHa /Fp${precompiled_header_clr_result}")
set(currsources ${currsources} src/ExampleAppClrPch.cpp)


set(sources ${sources} ${currsources})

source_group(\\windows_src\\ FILES ${currsources})
include(src/AboutPage/CMakeLists.txt)
include(src/ApplicationConfig/CMakeLists.txt)
include(src/AttractModeOverlay/CMakeLists.txt)
include(src/CLI/CMakeLists.txt)
include(src/Compass/CMakeLists.txt)
include(src/FlattenButton/CMakeLists.txt)
include(src/GpsMarkerTutorial/CMakeLists.txt)
include(src/Helpers/CMakeLists.txt)
include(src/InitialExperience/CMakeLists.txt)
include(src/InteriorsExplorer/CMakeLists.txt)
include(src/Menu/CMakeLists.txt)
include(src/Metrics/CMakeLists.txt)
include(src/ModalBackground/CMakeLists.txt)
include(src/MyPinCreation/CMakeLists.txt)
include(src/MyPinCreationDetails/CMakeLists.txt)
include(src/MyPinDetails/CMakeLists.txt)
include(src/MyPins/CMakeLists.txt)
include(src/Options/CMakeLists.txt)
include(src/PersistentSettings/CMakeLists.txt)
include(src/SearchMenu/CMakeLists.txt)
include(src/SearchResultPoi/CMakeLists.txt)
include(src/SearchResultSection/CMakeLists.txt)
include(src/SettingsMenu/CMakeLists.txt)
include(src/Surveys/CMakeLists.txt)
include(src/TagSearch/CMakeLists.txt)
include(src/VirtualKeyboard/CMakeLists.txt)
include(src/Watermark/CMakeLists.txt)
include(src/WindowsAppThreadAssertions/CMakeLists.txt)
