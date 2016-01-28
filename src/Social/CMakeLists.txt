set(headers ${headers} ../src/Social
)
set(currsources
  ../src/Social/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\Social FILES ${currsources})
include(../src/Social/TwitterFeed/CMakeLists.txt)
