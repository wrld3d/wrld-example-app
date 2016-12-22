set(headers ${headers} src/VirtualKeyboard
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\VirtualKeyboard FILES ${currsources})
include(src/VirtualKeyboard/View/CMakeLists.txt)
