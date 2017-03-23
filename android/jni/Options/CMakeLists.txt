if(${ANDROID})
set(headers ${headers} jni/Options
)
set(currsources
  jni/Options/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Options FILES ${currsources})
include(jni/Options/SdkModel/CMakeLists.txt)
include(jni/Options/View/CMakeLists.txt)
endif(${ANDROID})
