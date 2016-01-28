set(headers ${headers} ../src/AboutPage
)
set(currsources
  ../src/AboutPage/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\AboutPage FILES ${currsources})
include(../src/AboutPage/View/CMakeLists.txt)
