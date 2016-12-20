set(headers ${headers} ../src/FixedLocation
)
set(currsources
  ../src/FixedLocation/CMakeLists.txt
  ../src/FixedLocation/FixedIndoorLocationService.cpp
  ../src/FixedLocation/FixedIndoorLocationService.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\FixedLocation FILES ${currsources})
