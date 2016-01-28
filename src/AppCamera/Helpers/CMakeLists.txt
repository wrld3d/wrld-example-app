set(headers ${headers} ../src/AppCamera/Helpers
)
set(currsources
  ../src/AppCamera/Helpers/AppCameraHelpers.cpp
  ../src/AppCamera/Helpers/AppCameraHelpers.h
  ../src/AppCamera/Helpers/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\AppCamera\\Helpers FILES ${currsources})
