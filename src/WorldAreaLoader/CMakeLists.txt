set(headers ${headers} src/WorldAreaLoader
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\WorldAreaLoader FILES ${currsources})
include(src/WorldAreaLoader/SdkModel/CMakeLists.txt)
