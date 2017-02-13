set(headers ${headers} ../src/InteriorsPosition/SdkModel
)
set(currsources
  ../src/InteriorsPosition/SdkModel/CMakeLists.txt
  ../src/InteriorsPosition/SdkModel/InteriorsLocationServiceProvider.cpp
  ../src/InteriorsPosition/SdkModel/InteriorsLocationServiceProvider.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsPosition\\SdkModel FILES ${currsources})
include(../src/InteriorsPosition/SdkModel/SenionLab/CMakeLists.txt)
