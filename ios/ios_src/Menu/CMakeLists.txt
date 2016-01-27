if(${IOS})
set(headers ${headers} ios/ios_src/Menu
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Menu FILES ${currsources})
include(ios/ios_src/Menu/View/CMakeLists.txt)
endif(${IOS})
