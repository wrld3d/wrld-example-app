# Absorb Android.mk

if(${ANDROID})
set(headers ${headers} jni
)
set(currsources
  jni/AppHost.h
  jni/AppHost.cpp
  jni/AppHostJni.h
  jni/AppHostJni.cpp
  jni/AppInputDelegate.h
  jni/AppInputDelegate.cpp
  jni/AppRunner.h
  jni/AppRunner.cpp
  jni/GlDisplayService.h
  jni/GlDisplayService.cpp
  jni/main.cpp
  jni/main.h
)
set(sources ${sources} ${currsources})
source_group(\\jni FILES ${currsources})
include(jni/AboutPage/CMakeLists.txt)
include(jni/AndroidAppThreadAssertions/CMakeLists.txt)
include(jni/ApplicationConfig/CMakeLists.txt)
include(jni/Automation/CMakeLists.txt)
include(jni/Compass/CMakeLists.txt)
include(jni/FlattenButton/CMakeLists.txt)
include(jni/Helpers/CMakeLists.txt)
include(jni/InitialExperience/CMakeLists.txt)
include(jni/InteriorsExplorer/CMakeLists.txt)
include(jni/InteriorsPosition/CMakeLists.txt)
include(jni/Menu/CMakeLists.txt)
include(jni/Metrics/CMakeLists.txt)
include(jni/ModalBackground/CMakeLists.txt)
include(jni/MyPinCreation/CMakeLists.txt)
include(jni/MyPinCreationDetails/CMakeLists.txt)
include(jni/MyPinDetails/CMakeLists.txt)
include(jni/MyPins/CMakeLists.txt)
include(jni/Options/CMakeLists.txt)
include(jni/PersistentSettings/CMakeLists.txt)
include(jni/SearchMenu/CMakeLists.txt)
include(jni/SearchResultPoi/CMakeLists.txt)
include(jni/SearchResultSection/CMakeLists.txt)
include(jni/SettingsMenu/CMakeLists.txt)
include(jni/Surveys/CMakeLists.txt)
include(jni/TagSearch/CMakeLists.txt)
include(jni/Watermark/CMakeLists.txt)
endif(${ANDROID})
