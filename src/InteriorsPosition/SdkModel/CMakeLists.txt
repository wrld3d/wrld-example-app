set(headers ${headers} ../src/InteriorsPosition/SdkModel
)
set(currsources
  ../src/InteriorsPosition/SdkModel/CMakeLists.txt
  ../src/InteriorsPosition/SdkModel/TestLocationService.cpp
  ../src/InteriorsPosition/SdkModel/TestLocationService.h
  ../src/InteriorsPosition/SdkModel/InteriorsLocationServiceProvider.cpp
  ../src/InteriorsPosition/SdkModel/InteriorsLocationServiceProvider.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsPosition\\SdkModel FILES ${currsources})
