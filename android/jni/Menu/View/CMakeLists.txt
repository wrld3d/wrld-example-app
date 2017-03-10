if(${ANDROID})
set(headers ${headers} jni/Menu/View
)
set(currsources
  jni/Menu/View/IMenuViewModule.h
  jni/Menu/View/MenuJni.h
  jni/Menu/View/MenuJni.cpp
  jni/Menu/View/MenuView.h
  jni/Menu/View/MenuView.cpp
  jni/Menu/View/MenuViewIncludes.h
  jni/Menu/View/MenuViewModule.h
  jni/Menu/View/MenuViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Menu\\View FILES ${currsources})
endif(${ANDROID})
