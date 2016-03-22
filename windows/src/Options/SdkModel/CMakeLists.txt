set(headers ${headers} src/Options/SdkModel
)
set(currsources
  src/Options/SdkModel/ClearCacheMessageHandler.cpp
  src/Options/SdkModel/ClearCacheMessageHandler.h
)

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Options\\SdkModel FILES ${currsources})
