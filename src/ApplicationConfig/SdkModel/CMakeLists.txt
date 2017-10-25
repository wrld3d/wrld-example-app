set(headers ${headers} ../src/ApplicationConfig/SdkModel
)
set(currsources
  ../src/ApplicationConfig/SdkModel/ApplicationConfigurationJsonParser.cpp
  ../src/ApplicationConfig/SdkModel/ApplicationConfigurationJsonParser.h
  ../src/ApplicationConfig/SdkModel/ApplicationConfigurationModule.cpp
  ../src/ApplicationConfig/SdkModel/ApplicationConfigurationModule.h
  ../src/ApplicationConfig/SdkModel/ApplicationConfigurationReader.cpp
  ../src/ApplicationConfig/SdkModel/ApplicationConfigurationReader.h
  ../src/ApplicationConfig/SdkModel/ApplicationConfigurationService.cpp
  ../src/ApplicationConfig/SdkModel/ApplicationConfigurationService.h
  ../src/ApplicationConfig/SdkModel/ApplicationInteriorTrackingConfig.cpp
  ../src/ApplicationConfig/SdkModel/ApplicationInteriorTrackingConfig.h
  ../src/ApplicationConfig/SdkModel/ApplicationInteriorTrackingInfo.cpp
  ../src/ApplicationConfig/SdkModel/ApplicationInteriorTrackingInfo.h
  ../src/ApplicationConfig/SdkModel/CMakeLists.txt
  ../src/ApplicationConfig/SdkModel/IApplicationConfigurationModule.h
  ../src/ApplicationConfig/SdkModel/IApplicationConfigurationParser.h
  ../src/ApplicationConfig/SdkModel/IApplicationConfigurationReader.h
  ../src/ApplicationConfig/SdkModel/IApplicationConfigurationService.h
  ../src/ApplicationConfig/SdkModel/IApplicationConfigurationVersionProvider.h
  ../src/ApplicationConfig/SdkModel/ApplicationFixedIndoorLocation.cpp
  ../src/ApplicationConfig/SdkModel/ApplicationFixedIndoorLocation.h
  ../src/ApplicationConfig/SdkModel/ApplicationMenuItemTagSearchConfig.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\ApplicationConfig\\SdkModel FILES ${currsources})
