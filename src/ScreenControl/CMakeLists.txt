set(headers ${headers} src/ScreenControl
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\ScreenControl FILES ${currsources})
include(src/ScreenControl/View/CMakeLists.txt)
