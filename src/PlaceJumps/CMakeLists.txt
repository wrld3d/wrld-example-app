set(headers ${headers} ../src/PlaceJumps
)
set(currsources
  ../src/PlaceJumps/CMakeLists.txt
  ../src/PlaceJumps/PlaceJumps.h
  ../src/PlaceJumps/PlaceJumpSelectedMessage.cpp
  ../src/PlaceJumps/PlaceJumpSelectedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\PlaceJumps FILES ${currsources})
include(../src/PlaceJumps/SdkModel/CMakeLists.txt)
include(../src/PlaceJumps/View/CMakeLists.txt)
