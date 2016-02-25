set(headers ${headers} src/SearchMenu
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\SearchMenu FILES ${currsources})
include(src/SearchMenu/View/CMakeLists.txt)
