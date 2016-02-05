set(headers ${headers} src/SearchResultPoi
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\SearchResultPoi FILES ${currsources})
include(src/SearchResultPoi/View/CMakeLists.txt)
