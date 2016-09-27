set(headers ${headers} ../src/DirectionResultSection/View
)
set(currsources
  ../src/DirectionResultSection/View/CMakeLists.txt
  ../src/DirectionResultSection/View/DirectionResultSectionController.cpp
  ../src/DirectionResultSection/View/DirectionResultSectionController.h

)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionResultSection\\View FILES ${currsources})