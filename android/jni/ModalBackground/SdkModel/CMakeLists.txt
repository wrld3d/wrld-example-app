if(${ANDROID})
set(headers ${headers} jni/ModalBackground/SdkModel
)
set(currsources
  jni/ModalBackground/SdkModel/CMakeLists.txt
  jni/ModalBackground/SdkModel/IModalBackgroundNativeViewModule.h
  jni/ModalBackground/SdkModel/ModalBackgroundNativeModalityObserver.h
  jni/ModalBackground/SdkModel/ModalBackgroundNativeView.h
  jni/ModalBackground/SdkModel/ModalBackgroundNativeView.cpp
  jni/ModalBackground/SdkModel/ModalBackgroundNativeViewModule.h
  jni/ModalBackground/SdkModel/ModalBackgroundNativeViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\ModalBackground\\SdkModel FILES ${currsources})
endif(${ANDROID})
