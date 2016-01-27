set(headers ${headers} src/InteriorsEntitiesPins
)
set(currsources
  src/InteriorsEntitiesPins/InteriorsEntitiesPins.h
)
set(sources ${sources} ${currsources})
source_group(\\InteriorsEntitiesPins FILES ${currsources})
include(src/InteriorsEntitiesPins/SdkModel/CMakeLists.txt)
