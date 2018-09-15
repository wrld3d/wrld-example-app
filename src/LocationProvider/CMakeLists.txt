set(headers ${headers} ../src/LocationProvider
)
set(currsources
  ../src/LocationProvider/CMakeLists.txt
  ../src/LocationProvider/ILocationProvider.h
  ../src/LocationProvider/LocationProvider.cpp
  ../src/LocationProvider/LocationProvider.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\LocationProvider FILES ${currsources})
