set(headers ${headers} src/Social
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\Social FILES ${currsources})
include(src/Social/TwitterFeed/CMakeLists.txt)
