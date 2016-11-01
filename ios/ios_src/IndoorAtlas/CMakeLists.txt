if(${IOS})
set(headers ${headers} ios_src/IndoorAtlas
)
set(currsources
  ios_src/IndoorAtlas/CMakeLists.txt
  ios_src/IndoorAtlas/IndoorAtlasLocationController.h
  ios_src/IndoorAtlas/IndoorAtlasLocationController.mm
  ios_src/IndoorAtlas/IndoorAtlasLocationManager.h
  ios_src/IndoorAtlas/IndoorAtlasLocationManager.mm
  ios_src/IndoorAtlas/IndoorAtlasLocationModule.h
  ios_src/IndoorAtlas/IndoorAtlasLocationModule.mm
  ios_src/IndoorAtlas/IndoorAtlasLocationService.h
  ios_src/IndoorAtlas/IndoorAtlasLocationService.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\IndoorAtlas FILES ${currsources})
endif(${IOS})
