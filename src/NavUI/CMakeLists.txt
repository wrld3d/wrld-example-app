set(headers ${headers} ../src/NavUI
)
set(currsources
  ../src/NavUI/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\NavUI FILES ${currsources})
include(../src/NavUI/View/CMakeLists.txt)
