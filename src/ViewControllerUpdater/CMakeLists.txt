set(headers ${headers} ../src/ViewControllerUpdater
)
set(currsources
  ../src/ViewControllerUpdater/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\ViewControllerUpdater FILES ${currsources})
include(../src/ViewControllerUpdater/View/CMakeLists.txt)
