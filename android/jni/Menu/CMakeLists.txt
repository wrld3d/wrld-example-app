if(${ANDROID})
set(headers ${headers} jni/Menu
)
set(currsources
  jni/Menu/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Menu FILES ${currsources})
include(jni/Menu/View/CMakeLists.txt)
include(jni/Menu/SdkModel/CMakeLists.txt)
endif(${ANDROID})
