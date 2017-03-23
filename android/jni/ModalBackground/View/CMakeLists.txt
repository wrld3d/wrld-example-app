if(${ANDROID})
set(headers ${headers} jni/ModalBackground/View
)
set(currsources
  jni/ModalBackground/View/CMakeLists.txt
  jni/ModalBackground/View/IModalBackgroundViewModule.h
  jni/ModalBackground/View/ModalBackgroundAggregateView.h
  jni/ModalBackground/View/ModalBackgroundAggregateView.cpp
  jni/ModalBackground/View/ModalBackgroundViewJni.h
  jni/ModalBackground/View/ModalBackgroundViewJni.cpp
  jni/ModalBackground/View/ModalBackgroundViewModule.h
  jni/ModalBackground/View/ModalBackgroundViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\ModalBackground\\View FILES ${currsources})
endif(${ANDROID})
