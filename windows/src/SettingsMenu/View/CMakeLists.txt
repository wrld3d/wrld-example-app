set(headers ${headers} src/SettingsMenu/View
)
set(currsources_noclr
  src/SettingsMenu/View/SettingsMenuViewModule.cpp
  src/SettingsMenu/View/SettingsMenuViewModule.h
  src/SettingsMenu/View/SettingsMenuView.h
)
set(currsources
  src/SettingsMenu/View/SettingsMenuViewImpl.cpp
  src/SettingsMenu/View/SettingsMenuViewImpl.h
  src/SettingsMenu/View/SettingsMenuView.cpp
  src/SettingsMenu/View/SettingsMenuCLI.cpp
  src/SettingsMenu/View/SettingsMenuCLI.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\SettingsMenu\\View FILES ${currsources} ${currsources_noclr})
