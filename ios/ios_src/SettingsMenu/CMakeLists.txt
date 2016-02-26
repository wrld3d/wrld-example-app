if(${IOS})
set(headers ${headers} ios_src/SettingsMenu
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SettingsMenu FILES ${currsources})
include(ios_src/SettingsMenu/View/CMakeLists.txt)
endif(${IOS})
