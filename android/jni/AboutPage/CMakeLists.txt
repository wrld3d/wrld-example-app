if(${ANDROID})
set(headers ${headers} jni/AboutPage
)
set(currsources
  jni/AboutPage/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\AboutPage FILES ${currsources})
include(jni/AboutPage/View/CMakeLists.txt)
endif(${ANDROID})
