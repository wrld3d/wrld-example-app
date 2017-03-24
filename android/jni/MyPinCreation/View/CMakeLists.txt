if(${ANDROID})
set(headers ${headers} jni/MyPinCreation/View
)
set(currsources
  jni/MyPinCreation/View/CMakeLists.txt
  jni/MyPinCreation/View/IMyPinCreationViewModule.h
  jni/MyPinCreation/View/MyPinCreationConfirmationView.h
  jni/MyPinCreation/View/MyPinCreationConfirmationView.cpp
  jni/MyPinCreation/View/MyPinCreationInitiationView.h
  jni/MyPinCreation/View/MyPinCreationInitiationView.cpp
  jni/MyPinCreation/View/MyPinCreationViewIncludes.h
  jni/MyPinCreation/View/MyPinCreationViewJni.h
  jni/MyPinCreation/View/MyPinCreationViewJni.cpp
  jni/MyPinCreation/View/MyPinCreationViewModule.h
  jni/MyPinCreation/View/MyPinCreationViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\MyPinCreation\\View FILES ${currsources})
endif(${ANDROID})
