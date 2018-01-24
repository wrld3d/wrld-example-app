if(${ANDROID})
set(headers ${headers} jni/NavRouting
)
set(currsources
  jni/NavRouting/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\NavRouting FILES ${currsources})
include(jni/NavRouting/View/CMakeLists.txt)
endif(${ANDROID})
