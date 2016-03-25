set(headers ${headers} ios_src/MyPins
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\\\MyPins FILES ${currsources})
include(ios_src/MyPins/View/CMakeLists.txt)
