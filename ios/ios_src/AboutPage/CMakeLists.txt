if(${IOS})
set(headers ${headers} ios/ios_src/AboutPage
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\AboutPage FILES ${currsources})
include(ios/ios_src/AboutPage/View/CMakeLists.txt)
endif(${IOS})
