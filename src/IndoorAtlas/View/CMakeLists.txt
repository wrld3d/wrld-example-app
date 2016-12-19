if(${IOS})
set(headers ${headers} ../src/IndoorAtlas/View
)
set(currsources
  ../src/IndoorAtlas/View/CMakeLists.txt
  ../src/IndoorAtlas/View/IIndoorAtlasLocationManager.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\IndoorAtlas\\View FILES ${currsources})
endif(${IOS})
