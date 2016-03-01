set(headers ${headers} ../src/SettingsMenu
)
set(currsources
  ../src/SettingsMenu/CMakeLists.txt
  ../src/SettingsMenu/SettingsMenu.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SettingsMenu FILES ${currsources})
include(../src/SettingsMenu/SdkModel/CMakeLists.txt)
include(../src/SettingsMenu/View/CMakeLists.txt)
