set(headers ${headers} ../src/SenionLocation
)
set(currsources
  ../src/SenionLocation/SenionLocation.h
  ../src/SenionLocation/AvatarVisibilityObserver.cpp
  ../src/SenionLocation/AvatarVisibilityObserver.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SenionLocation FILES ${currsources})
include(../src/SenionLocation/SdkModel/CMakeLists.txt)
