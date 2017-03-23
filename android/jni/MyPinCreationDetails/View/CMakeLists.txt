if(${ANDROID})
set(headers ${headers} jni/MyPinCreationDetails/View
)
set(currsources
  jni/MyPinCreationDetails/View/CMakeLists.txt
  jni/MyPinCreationDetails/View/IMyPinCreationDetailsViewModule.h
  jni/MyPinCreationDetails/View/MyPinCreationDetailsView.h
  jni/MyPinCreationDetails/View/MyPinCreationDetailsView.cpp
  jni/MyPinCreationDetails/View/MyPinCreationDetailsViewIncludes.h
  jni/MyPinCreationDetails/View/MyPinCreationDetailsViewJni.h
  jni/MyPinCreationDetails/View/MyPinCreationDetailsViewJni.cpp
  jni/MyPinCreationDetails/View/MyPinCreationDetailsViewModule.h
  jni/MyPinCreationDetails/View/MyPinCreationDetailsViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\MyPinCreationDetails\\View FILES ${currsources})
endif(${ANDROID})
