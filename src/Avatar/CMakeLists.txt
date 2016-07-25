set(headers ${headers} ../src/Avatar
)
set(currsources
  ../src/Avatar/Avatar.h
  ../src/Avatar/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\Avatar FILES ${currsources})
include(../src/Avatar/SdkModel/CMakeLists.txt)
include(../src/Avatar/AvatarModule/CMakeLists.txt)
