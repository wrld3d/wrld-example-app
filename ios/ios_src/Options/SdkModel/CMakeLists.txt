if(${IOS})
set(headers ${headers} ios_src/Options/SdkModel
)
set(currsources
  ios_src/Options/SdkModel/CacheClearBackgroundTask.cpp
  ios_src/Options/SdkModel/CacheClearBackgroundTask.h
  ios_src/Options/SdkModel/ClearCacheMessageHandler.h
  ios_src/Options/SdkModel/ClearCacheMessageHandler.mm
  ios_src/Options/SdkModel/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Options\\SdkModel FILES ${currsources})
endif(${IOS})
