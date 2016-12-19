if(${IOS})
set(headers ${headers} ios_src/IndoorAtlas
)
set(currsources
  ios_src/IndoorAtlas/CMakeLists.txt
  ios_src/IndoorAtlas/IndoorAtlasLocationModule.h
  ios_src/IndoorAtlas/IndoorAtlasLocationModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\IndoorAtlas FILES ${currsources})
include(ios_src/IndoorAtlas/View/CMakeLists.txt)

endif(${IOS})
