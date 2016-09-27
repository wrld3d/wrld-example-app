set(headers ${headers} ios_src/DirectionResultSection
)
set(currsources
  ios_src/DirectionResultSection/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\DirectionResultSection FILES ${currsources})
include(ios_src/DirectionResultSection/View/CMakeLists.txt)
