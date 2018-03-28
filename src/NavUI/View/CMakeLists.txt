set(headers ${headers} ../src/NavUI/View
)
set(currsources
  ../src/NavUI/View/NavUIModule.cpp
  ../src/NavUI/View/NavUIModule.h
  ../src/NavUI/View/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\NavUI\\View FILES ${currsources})
