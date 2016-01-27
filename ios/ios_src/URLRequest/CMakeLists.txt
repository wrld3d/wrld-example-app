if(${IOS})
set(headers ${headers} ios/ios_src/URLRequest
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\URLRequest FILES ${currsources})
include(ios/ios_src/URLRequest/View/CMakeLists.txt)
endif(${IOS})
