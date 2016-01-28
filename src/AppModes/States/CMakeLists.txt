set(headers ${headers} ../src/AppModes/States
)
set(currsources
  ../src/AppModes/States/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\AppModes\\States FILES ${currsources})
include(../src/AppModes/States/SdkModel/CMakeLists.txt)
