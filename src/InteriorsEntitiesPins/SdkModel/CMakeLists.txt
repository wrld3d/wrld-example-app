set(headers ${headers} ../src/InteriorsEntitiesPins/SdkModel
)
set(currsources
  ../src/InteriorsEntitiesPins/SdkModel/CMakeLists.txt
  ../src/InteriorsEntitiesPins/SdkModel/IInteriorsEntitiesPinsController.h
  ../src/InteriorsEntitiesPins/SdkModel/IInteriorsEntitiesPinsModule.h
  ../src/InteriorsEntitiesPins/SdkModel/InteriorsEntitiesPinsController.cpp
  ../src/InteriorsEntitiesPins/SdkModel/InteriorsEntitiesPinsController.h
  ../src/InteriorsEntitiesPins/SdkModel/InteriorsEntitiesPinsModule.cpp
  ../src/InteriorsEntitiesPins/SdkModel/InteriorsEntitiesPinsModule.h
  ../src/InteriorsEntitiesPins/SdkModel/InteriorsEntityPinData.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InteriorsEntitiesPins\\SdkModel FILES ${currsources})
