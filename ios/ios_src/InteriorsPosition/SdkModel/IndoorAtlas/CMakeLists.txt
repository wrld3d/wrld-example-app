if(${IOS})
set(headers ${headers} ios_src/InteriorsPosition/SdkModel/IndoorAtlas
)
set(currsources
  ios_src/InteriorsPosition/SdkModel/IndoorAtlas/CMakeLists.txt
  ios_src/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationManager.h
  ios_src/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationManager.mm
  ios_src/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationManagerObjC.h
  ios_src/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationManagerObjC.mm
  ios_src/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationModule.h
  ios_src/InteriorsPosition/SdkModel/IndoorAtlas/IndoorAtlasLocationModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\InteriorsPosition\\SdkModel\\IndoorAtlas FILES ${currsources})
endif(${IOS})
