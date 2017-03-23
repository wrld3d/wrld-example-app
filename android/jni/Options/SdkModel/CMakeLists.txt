if(${ANDROID})
set(headers ${headers} jni/Options/SdkModel
)
set(currsources
  jni/Options/SdkModel/ClearCacheMessageHandler.h
  jni/Options/SdkModel/ClearCacheMessageHandler.cpp
  jni/Options/SdkModel/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Options\\SdkModel FILES ${currsources})
endif(${ANDROID})
