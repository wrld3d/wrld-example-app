set(headers ${headers} ../src/ScreenControl
)
set(currsources
  ../src/ScreenControl/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\ScreenControl FILES ${currsources})
include(../src/ScreenControl/View/CMakeLists.txt)
