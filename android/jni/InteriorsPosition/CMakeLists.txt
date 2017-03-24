if(${ANDROID})
set(headers ${headers} jni/InteriorsPosition
)
set(currsources
  jni/InteriorsPosition/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InteriorsPosition FILES ${currsources})
include(jni/InteriorsPosition/SdkModel/CMakeLists.txt)
include(jni/InteriorsPosition/View/CMakeLists.txt)
endif(${ANDROID})
