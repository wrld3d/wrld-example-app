if(${IOS})
set(headers ${headers} ios_src/ApplicationConfig/SdkModel
)
set(currsources
  ios_src/ApplicationConfig/SdkModel/CMakeLists.txt
  ios_src/ApplicationConfig/SdkModel/iOSApplicationConfigurationVersionProvider.h
  ios_src/ApplicationConfig/SdkModel/iOSApplicationConfigurationVersionProvider.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\ApplicationConfig\\SdkModel FILES ${currsources})
endif(${IOS})
