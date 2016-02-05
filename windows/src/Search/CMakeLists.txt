set(headers ${headers} src/Search
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Search FILES ${currsources})
include(src/Search/Yelp/CMakeLists.txt)
