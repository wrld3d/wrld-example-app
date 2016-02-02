set(headers ${headers} src/MyPinDetails
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\MyPinDetails FILES ${currsources})
include(src/MyPinDetails/View/CMakeLists.txt)
