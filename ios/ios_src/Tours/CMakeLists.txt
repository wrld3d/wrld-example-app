if(${IOS})
set(headers ${headers} ios/ios_src/Tours
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Tours FILES ${currsources})
include(ios/ios_src/Tours/View/CMakeLists.txt)
endif(${IOS})
