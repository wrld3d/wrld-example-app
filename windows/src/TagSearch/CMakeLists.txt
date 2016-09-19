set(headers ${headers} src/TagSearch
)
set(currsources
  src/TagSearch/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\TagSearch FILES ${currsources})
include(src/TagSearch/View/CMakeLists.txt)
