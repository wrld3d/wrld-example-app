if(${ANDROID})
set(headers ${headers} jni/ModalBackground
)
set(currsources
  jni/ModalBackground/CMakeLists.txt
  jni/ModalBackground/ModalBackgroundViewIncludes.h
)
set(sources ${sources} ${currsources})
source_group(\\jni\\ModalBackground FILES ${currsources})
include(jni/ModalBackground/SdkModel/CMakeLists.txt)
include(jni/ModalBackground/View/CMakeLists.txt)
endif(${ANDROID})
