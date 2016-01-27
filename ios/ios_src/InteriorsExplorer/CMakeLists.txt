if(${IOS})
set(headers ${headers} ios/ios_src/InteriorsExplorer
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\InteriorsExplorer FILES ${currsources})
include(ios/ios_src/InteriorsExplorer/View/CMakeLists.txt)
endif(${IOS})
