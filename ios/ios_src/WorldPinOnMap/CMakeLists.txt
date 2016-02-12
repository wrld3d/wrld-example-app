if(${IOS})
set(headers ${headers} ios_src/WorldPinOnMap
)
set(currsources
  ios_src/WorldPinOnMap/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\WorldPinOnMap FILES ${currsources})
include(ios_src/WorldPinOnMap/View/CMakeLists.txt)
endif(${IOS})
