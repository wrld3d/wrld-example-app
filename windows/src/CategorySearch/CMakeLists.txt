set(headers ${headers} src/CategorySearch
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\CategorySearch FILES ${currsources})
include(src/CategorySearch/View/CMakeLists.txt)
