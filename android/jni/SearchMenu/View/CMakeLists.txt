if(${ANDROID})
set(headers ${headers} jni/SearchMenu/View
)
set(currsources
  jni/SearchMenu/View/SearchMenuJni.cpp
  jni/SearchMenu/View/SearchMenuJni.h
  jni/SearchMenu/View/SearchMenuView.h
  jni/SearchMenu/View/SearchMenuView.cpp
  jni/SearchMenu/View/SearchMenuViewModule.h
  jni/SearchMenu/View/SearchMenuViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\SearchMenu\\View FILES ${currsources})
endif(${ANDROID})
