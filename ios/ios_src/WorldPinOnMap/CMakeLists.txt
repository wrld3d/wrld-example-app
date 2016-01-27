if(${IOS})
set(headers ${headers} ios/ios_src/WorldPinOnMap
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\WorldPinOnMap FILES ${currsources})
include(ios/ios_src/WorldPinOnMap/View/CMakeLists.txt)
endif(${IOS})
