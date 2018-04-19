set(headers ${headers} ../src/SettingsMenu/View
)
set(currsources
  ../src/SettingsMenu/View/CMakeLists.txt
  ../src/SettingsMenu/View/ISettingsMenuView.h
  ../src/SettingsMenu/View/SettingsMenuController.cpp
  ../src/SettingsMenu/View/SettingsMenuController.h
  ../src/SettingsMenu/View/DesktopSettingsMenuController.cpp
  ../src/SettingsMenu/View/DesktopSettingsMenuController.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SettingsMenu\\View FILES ${currsources})
