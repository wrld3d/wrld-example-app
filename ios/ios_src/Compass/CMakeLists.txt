if(${IOS})
set(headers ${headers} ios/ios_src/Compass
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Compass FILES ${currsources})
include(ios/ios_src/Compass/View/CMakeLists.txt)
endif(${IOS})
