set(headers ${headers} src/SettingsMenu/View
)
set(currsources
  src/SettingsMenu/View/ISettingsMenuViewModule.h
  src/SettingsMenu/View/SettingsMenuView.h
  src/SettingsMenu/View/SettingsMenuView.cpp
  src/SettingsMenu/View/SettingsMenuCLI.cpp
  src/SettingsMenu/View/SettingsMenuCLI.h
  src/SettingsMenu/View/SettingsMenuViewModule.cpp
  src/SettingsMenu/View/SettingsMenuViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\SettingsMenu\\View FILES ${currsources})
