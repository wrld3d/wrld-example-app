set(headers ${headers} src/Options
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Options FILES ${currsources})
include(src/Options/SdkModel/CMakeLists.txt)
include(src/Options/View/CMakeLists.txt)
