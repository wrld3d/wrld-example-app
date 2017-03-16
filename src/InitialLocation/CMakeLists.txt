set(headers ${headers} ../src/InitialLocation
)
set(currsources
../src/InitialLocation/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\InitialLocation FILES ${currsources})
include(../src/InitialLocation/SdkModel/CMakeLists.txt)
