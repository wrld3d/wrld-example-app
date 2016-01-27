if(${IOS})
set(headers ${headers} ios/ios_src/MyPinCreationDetails
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\MyPinCreationDetails FILES ${currsources})
include(ios/ios_src/MyPinCreationDetails/View/CMakeLists.txt)
endif(${IOS})
