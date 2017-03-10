if(${ANDROID})
set(headers ${headers} jni/FlattenButton/View
)
set(currsources
  jni/FlattenButton/View/CMakeLists.txt
  jni/FlattenButton/View/FlattenButtonView.h
  jni/FlattenButton/View/FlattenButtonView.cpp
  jni/FlattenButton/View/FlattenButtonViewIncludes.h
  jni/FlattenButton/View/FlattenButtonJni.h
  jni/FlattenButton/View/FlattenButtonJni.cpp
  jni/FlattenButton/View/FlattenButtonViewModule.h
  jni/FlattenButton/View/FlattenButtonViewModule.cpp
  jni/FlattenButton/View/IFlattenButtonViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\jni\\FlattenButton\\View FILES ${currsources})
endif(${ANDROID})
