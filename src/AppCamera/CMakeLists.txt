set(headers ${headers} ../src/AppCamera
)
set(currsources
  ../src/AppCamera/AppCamera.h
  ../src/AppCamera/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\AppCamera FILES ${currsources})
include(../src/AppCamera/Helpers/CMakeLists.txt)
include(../src/AppCamera/SdkModel/CMakeLists.txt)
