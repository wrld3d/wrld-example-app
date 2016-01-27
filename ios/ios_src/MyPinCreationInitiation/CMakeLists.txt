if(${IOS})
set(headers ${headers} ios/ios_src/MyPinCreationInitiation
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\MyPinCreationInitiation FILES ${currsources})
include(ios/ios_src/MyPinCreationInitiation/View/CMakeLists.txt)
endif(${IOS})
