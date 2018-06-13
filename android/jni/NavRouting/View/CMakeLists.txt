if(${ANDROID})
set(headers ${headers} jni/NavRouting/View
)
set(currsources
  jni/NavRouting/View/CMakeLists.txt
  jni/NavRouting/View/INavWidgetViewModule.h
  jni/NavRouting/View/NavWidgetJni.h
  jni/NavRouting/View/NavWidgetJni.cpp
  jni/NavRouting/View/NavWidgetView.h
  jni/NavRouting/View/NavWidgetView.cpp
  jni/NavRouting/View/NavWidgetViewIncludes.h
  jni/NavRouting/View/NavWidgetViewModule.h
  jni/NavRouting/View/NavWidgetViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\NavRouting\\View FILES ${currsources})
endif(${ANDROID})
