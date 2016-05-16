set(headers ${headers} src/MyPins
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\MyPins FILES ${currsources})
include(src/MyPins/View/CMakeLists.txt)
