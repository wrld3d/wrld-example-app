if(${ANDROID})
set(headers ${headers} jni/ApplicationConfig/SdkModel
)
set(currsources
  jni/ApplicationConfig/SdkModel/CMakeLists.txt
  jni/ApplicationConfig/SdkModel/AndroidApplicationConfigurationVersionProvider.h
  jni/ApplicationConfig/SdkModel/AndroidApplicationConfigurationVersionProvider.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\ApplicationConfig\\SdkModel FILES ${currsources})
endif(${ANDROID})
