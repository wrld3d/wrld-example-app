set(headers ${headers} ../src/Options/SdkModel
)
set(currsources
  ../src/Options/SdkModel/CacheEnabledChangedMessageHandler.cpp
  ../src/Options/SdkModel/CacheEnabledChangedMessageHandler.h
  ../src/Options/SdkModel/CMakeLists.txt
  ../src/Options/SdkModel/OptionsSdkIncludes.h
  ../src/Options/SdkModel/StreamOverWifiOnlyChangedMessageHandler.cpp
  ../src/Options/SdkModel/StreamOverWifiOnlyChangedMessageHandler.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Options\\SdkModel FILES ${currsources})
