if(${IOS})
set(headers ${headers} ios/ios_src/Options
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Options FILES ${currsources})
include(ios/ios_src/Options/SdkModel/CMakeLists.txt)
include(ios/ios_src/Options/View/CMakeLists.txt)
endif(${IOS})
