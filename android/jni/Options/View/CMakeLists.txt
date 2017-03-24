if(${ANDROID})
set(headers ${headers} jni/Options/View
)
set(currsources
  jni/Options/View/CMakeLists.txt
  jni/Options/View/IOptionsViewModule.h
  jni/Options/View/OptionsView.h
  jni/Options/View/OptionsView.cpp
  jni/Options/View/OptionsViewIncludes.h
  jni/Options/View/OptionsJni.h
  jni/Options/View/OptionsJni.cpp
  jni/Options/View/OptionsViewModule.h
  jni/Options/View/OptionsViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Options\\View FILES ${currsources})
endif(${ANDROID})
