set(headers ${headers} ../src/InteriorsPosition/SdkModel/IndoorAtlas
)
set(currsources
  ../src/InteriorsPosition/SdkModel/IndoorAtlas/CMakeLists.txt
  ../src/InteriorsPosition/SdkModel/IndoorAtlas/IIndoorAtlasLocationManager.h
  ../src/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationController.cpp
  ../src/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationController.h
  ../src/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationService.cpp
  ../src/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationService.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsPosition\\SdkModel\\IndoorAtlas FILES ${currsources})
