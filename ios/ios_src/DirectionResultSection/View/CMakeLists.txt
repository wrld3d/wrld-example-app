set(headers ${headers} ios_src/DirectionResultSection/View
)
set(currsources
  ios_src/DirectionResultSection/View/CMakeLists.txt
  ios_src/DirectionResultSection/View/DirectionResultSectionViewModule.mm
  ios_src/DirectionResultSection/View/DirectionResultSectionViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\DirectionResultSection\\View FILES ${currsources})