set(headers ${headers} src/Compass
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\Compass FILES ${currsources})
include(src/Compass/View/CMakeLists.txt)
