if(${IOS})
set(headers ${headers} ios/ios_src/ApplicationConfig
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\ApplicationConfig FILES ${currsources})
include(ios/ios_src/ApplicationConfig/SdkModel/CMakeLists.txt)
endif(${IOS})
