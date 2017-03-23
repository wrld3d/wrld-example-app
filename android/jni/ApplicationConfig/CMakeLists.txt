if(${ANDROID})
set(headers ${headers} jni/ApplicationConfig
)
set(currsources
  jni/ApplicationConfig/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\ApplicationConfig FILES ${currsources})
include(jni/ApplicationConfig/SdkModel/CMakeLists.txt)
endif(${ANDROID})
