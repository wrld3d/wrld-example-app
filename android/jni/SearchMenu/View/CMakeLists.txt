if(${ANDROID})
set(headers ${headers} jni/SearchMenu/View
)
set(currsources
  jni/SearchMenu/View/SearchMenuJni.cpp
  jni/SearchMenu/View/SearchMenuJni.h
  jni/SearchMenu/View/SearchMenuView.h
  jni/SearchMenu/View/SearchMenuView.cpp
  jni/SearchMenu/View/SearchWidgetJni.cpp
  jni/SearchMenu/View/SearchWidgetJni.h
  jni/SearchMenu/View/SearchWidgetView.h
  jni/SearchMenu/View/SearchWidgetView.cpp
  jni/SearchMenu/View/SearchWidgetViewModule.h
  jni/SearchMenu/View/SearchWidgetViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\SearchMenu\\View FILES ${currsources})
endif(${ANDROID})
