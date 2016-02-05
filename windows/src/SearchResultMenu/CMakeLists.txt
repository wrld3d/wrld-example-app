set(headers ${headers} src/SearchResultMenu
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\SearchResultMenu FILES ${currsources})
include(src/SearchResultMenu/View/CMakeLists.txt)
