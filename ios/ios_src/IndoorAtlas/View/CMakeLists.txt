if(${IOS})
set(headers ${headers} ios_src/IndoorAtlas/View
)
set(currsources
  ios_src/IndoorAtlas/View/CMakeLists.txt
  ios_src/IndoorAtlas/View/IndoorAtlasLocationManager.h
  ios_src/IndoorAtlas/View/IndoorAtlasLocationManager.mm
  ios_src/IndoorAtlas/View/IndoorAtlasLocationManagerInterop.h
  ios_src/IndoorAtlas/View/IndoorAtlasLocationManagerInterop.mm
  ios_src/IndoorAtlas/View/IndoorAtlasLocationIncludes.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\IndoorAtlas\\View FILES ${currsources})

endif(${IOS})
