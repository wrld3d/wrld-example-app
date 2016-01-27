if(${IOS})
set(headers ${headers} ios/ios_src/MyPinCreationConfirmation
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\MyPinCreationConfirmation FILES ${currsources})
include(ios/ios_src/MyPinCreationConfirmation/View/CMakeLists.txt)
endif(${IOS})
