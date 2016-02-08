set(headers ${headers} src/MyPinCreationDetails
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\MyPinCreationDetails FILES ${currsources})
include(src/MyPinCreationDetails/View/CMakeLists.txt)
