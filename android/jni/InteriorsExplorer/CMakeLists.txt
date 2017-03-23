if(${ANDROID})
set(headers ${headers} jni/InteriorsExplorer
)
set(currsources
  jni/InteriorsExplorer/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InteriorsExplorer FILES ${currsources})
include(jni/InteriorsExplorer/View/CMakeLists.txt)
endif(${ANDROID})
