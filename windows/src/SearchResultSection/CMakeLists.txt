set(headers ${headers} src/SearchResultSection
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\SearchResultSection FILES ${currsources})
include(src/SearchResultSection/View/CMakeLists.txt)
