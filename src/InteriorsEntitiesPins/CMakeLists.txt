set(headers ${headers} ../src/InteriorsEntitiesPins
)
set(currsources
  ../src/InteriorsEntitiesPins/CMakeLists.txt
  ../src/InteriorsEntitiesPins/InteriorsEntitiesPins.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsEntitiesPins FILES ${currsources})
include(../src/InteriorsEntitiesPins/SdkModel/CMakeLists.txt)
