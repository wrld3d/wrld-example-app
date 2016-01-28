set(headers ${headers} ../src/OpenableControl
)
set(currsources
  ../src/OpenableControl/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\OpenableControl FILES ${currsources})
include(../src/OpenableControl/View/CMakeLists.txt)
