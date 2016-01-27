if(${IOS})
set(headers ${headers} ios/ios_src/MyPinDetails
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\MyPinDetails FILES ${currsources})
include(ios/ios_src/MyPinDetails/View/CMakeLists.txt)
endif(${IOS})
