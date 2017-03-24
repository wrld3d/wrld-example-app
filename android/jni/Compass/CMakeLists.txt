if(${ANDROID})
set(headers ${headers} jni/Compass
)
set(currsources
  jni/Compass/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Compass FILES ${currsources})
include(jni/Compass/View/CMakeLists.txt)
endif(${ANDROID})
