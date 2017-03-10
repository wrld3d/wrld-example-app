if(${ANDROID})
set(headers ${headers} jni/MyPinDetails/View
)
set(currsources
  jni/MyPinDetails/View/CMakeLists.txt
  jni/MyPinDetails/View/IMyPinDetailsViewModule.h
  jni/MyPinDetails/View/MyPinDetailsView.h
  jni/MyPinDetails/View/MyPinDetailsView.cpp
  jni/MyPinDetails/View/MyPinDetailsViewIncludes.h
  jni/MyPinDetails/View/MyPinDetailsViewJni.h
  jni/MyPinDetails/View/MyPinDetailsViewJni.cpp
  jni/MyPinDetails/View/MyPinDetailsViewModule.h
  jni/MyPinDetails/View/MyPinDetailsViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\MyPinDetails\\View FILES ${currsources})
endif(${ANDROID})
