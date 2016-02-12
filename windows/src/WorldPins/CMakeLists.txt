set(headers ${headers} src/WorldPins
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\WorldPins FILES ${currsources})
include(src/WorldPins/View/CMakeLists.txt)
