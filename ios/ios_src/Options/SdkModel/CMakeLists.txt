if(${IOS})
set(headers ${headers} ios/ios_src/Options/SdkModel
)
set(currsources
  ios/ios_src/Options/SdkModel/CacheClearBackgroundTask.cpp
  ios/ios_src/Options/SdkModel/CacheClearBackgroundTask.h
  ios/ios_src/Options/SdkModel/ClearCacheMessageHandler.h
  ios/ios_src/Options/SdkModel/ClearCacheMessageHandler.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Options\\SdkModel FILES ${currsources})
endif(${IOS})
