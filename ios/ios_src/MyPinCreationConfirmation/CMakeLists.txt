if(${IOS})
set(headers ${headers} ios_src/MyPinCreationConfirmation
)
set(currsources
  ios_src/MyPinCreationConfirmation/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\MyPinCreationConfirmation FILES ${currsources})
include(ios_src/MyPinCreationConfirmation/View/CMakeLists.txt)
endif(${IOS})
