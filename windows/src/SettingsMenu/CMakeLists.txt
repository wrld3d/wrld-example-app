set(headers ${headers} src/SettingsMenu
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\SettingsMenu FILES ${currsources})
include(src/SettingsMenu/View/CMakeLists.txt)
