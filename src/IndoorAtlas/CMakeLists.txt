if(${IOS})
set(headers ${headers} ../src/IndoorAtlas
)
set(currsources
  ../src/IndoorAtlas/CMakeLists.txt
  ../src/IndoorAtlas/IndoorAtlasLocationController.h
  ../src/IndoorAtlas/IndoorAtlasLocationController.cpp
  ../src/IndoorAtlas/IndoorAtlasLocationService.h
  ../src/IndoorAtlas/IndoorAtlasLocationService.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\IndoorAtlas FILES ${currsources})
endif(${IOS})
