set(headers ${headers} ../src/ApplicationConfig
)
set(currsources
  ../src/ApplicationConfig/ApplicationConfig.h
  ../src/ApplicationConfig/ApplicationConfiguration.cpp
  ../src/ApplicationConfig/ApplicationConfiguration.h
  ../src/ApplicationConfig/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\ApplicationConfig FILES ${currsources})
include(../src/ApplicationConfig/SdkModel/CMakeLists.txt)
