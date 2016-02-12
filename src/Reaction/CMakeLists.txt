set(headers ${headers} ../src/Reaction
)
set(currsources
  ../src/Reaction/CMakeLists.txt
  ../src/Reaction/Reaction.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Reaction FILES ${currsources})
include(../src/Reaction/View/CMakeLists.txt)
