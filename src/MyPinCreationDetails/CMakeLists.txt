set(headers ${headers} src/MyPinCreationDetails
)
set(currsources
  src/MyPinCreationDetails/MyPinCreationDetails.h
)
set(sources ${sources} ${currsources})
source_group(\\MyPinCreationDetails FILES ${currsources})
include(src/MyPinCreationDetails/View/CMakeLists.txt)
