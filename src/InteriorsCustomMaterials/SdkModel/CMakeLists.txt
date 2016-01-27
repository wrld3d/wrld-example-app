set(headers ${headers} src/InteriorsCustomMaterials/SdkModel
)
set(currsources
  src/InteriorsCustomMaterials/SdkModel/IInteriorsCustomMaterialDtoRepository.h
  src/InteriorsCustomMaterials/SdkModel/IInteriorsCustomMaterialsModule.h
  src/InteriorsCustomMaterials/SdkModel/InteriorsCustomMaterialDto.h
  src/InteriorsCustomMaterials/SdkModel/InteriorsCustomMaterialDtoRepository.cpp
  src/InteriorsCustomMaterials/SdkModel/InteriorsCustomMaterialDtoRepository.h
  src/InteriorsCustomMaterials/SdkModel/InteriorsCustomMaterialFactory.cpp
  src/InteriorsCustomMaterials/SdkModel/InteriorsCustomMaterialFactory.h
  src/InteriorsCustomMaterials/SdkModel/InteriorsCustomMaterialKeys.h
  src/InteriorsCustomMaterials/SdkModel/InteriorsCustomMaterialParser.cpp
  src/InteriorsCustomMaterials/SdkModel/InteriorsCustomMaterialParser.h
  src/InteriorsCustomMaterials/SdkModel/InteriorsCustomMaterialsModule.cpp
  src/InteriorsCustomMaterials/SdkModel/InteriorsCustomMaterialsModule.h
)
set(sources ${sources} ${currsources})
source_group(\\InteriorsCustomMaterials\\SdkModel FILES ${currsources})
