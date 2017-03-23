if(${ANDROID})
set(headers ${headers} jni/AboutPage/View
)
set(currsources
  jni/AboutPage/View/AboutPageJni.h
  jni/AboutPage/View/AboutPageJni.cpp
  jni/AboutPage/View/AboutPageView.h
  jni/AboutPage/View/AboutPageView.cpp
  jni/AboutPage/View/AboutPageViewIncludes.h
  jni/AboutPage/View/AboutPageViewModule.h
  jni/AboutPage/View/AboutPageViewModule.cpp
  jni/AboutPage/View/CMakeLists.txt
  jni/AboutPage/View/IAboutPageViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\jni\\AboutPage\\View FILES ${currsources})
endif(${ANDROID})
