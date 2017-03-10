if(${ANDROID})
set(headers ${headers} jni/FlattenButton
)
set(currsources
  jni/FlattenButton/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\FlattenButton FILES ${currsources})
include(jni/FlattenButton/View/CMakeLists.txt)
endif(${ANDROID})
