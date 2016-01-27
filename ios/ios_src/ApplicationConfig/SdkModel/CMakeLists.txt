if(${IOS})
set(headers ${headers} ios/ios_src/ApplicationConfig/SdkModel
)
set(currsources
  ios/ios_src/ApplicationConfig/SdkModel/iOSApplicationConfigurationVersionProvider.h
  ios/ios_src/ApplicationConfig/SdkModel/iOSApplicationConfigurationVersionProvider.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\ApplicationConfig\\SdkModel FILES ${currsources})
endif(${IOS})
