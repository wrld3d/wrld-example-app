set(headers ${headers} src/MyPinCreation
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\MyPinCreation FILES ${currsources})
include(src/MyPinCreation/View/CMakeLists.txt)
