set(headers ${headers} src/Reaction
)
set(currsources
  src/Reaction/Reaction.h
)
set(sources ${sources} ${currsources})
source_group(\\Reaction FILES ${currsources})
include(src/Reaction/View/CMakeLists.txt)
