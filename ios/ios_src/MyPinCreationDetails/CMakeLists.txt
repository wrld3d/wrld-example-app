if(${IOS})
set(headers ${headers} ios_src/MyPinCreationDetails
)
set(currsources
  ios_src/MyPinCreationDetails/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\MyPinCreationDetails FILES ${currsources})
include(ios_src/MyPinCreationDetails/View/CMakeLists.txt)
endif(${IOS})
