set(headers ${headers} ../src/MyPinCreationDetails
)
set(currsources
  ../src/MyPinCreationDetails/CMakeLists.txt
  ../src/MyPinCreationDetails/MyPinCreationDetails.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MyPinCreationDetails FILES ${currsources})
include(../src/MyPinCreationDetails/View/CMakeLists.txt)
