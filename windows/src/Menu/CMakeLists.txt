set(headers ${headers} src/Menu
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Menu FILES ${currsources})
include(src/Menu/View/CMakeLists.txt)
include(src/Menu/SdkModel/CMakeLists.txt)
