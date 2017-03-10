if(${ANDROID})
set(headers ${headers} jni/InteriorsPosition/View
)
set(currsources
  jni/InteriorsPosition/View/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InteriorsPosition\\View FILES ${currsources})
include(jni/InteriorsPosition/View/SenionLab/CMakeLists.txt)
endif(${ANDROID})
