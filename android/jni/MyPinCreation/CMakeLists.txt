if(${ANDROID})
set(headers ${headers} jni/MyPinCreation
)
set(currsources
  jni/MyPinCreation/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\MyPinCreation FILES ${currsources})
include(jni/MyPinCreation/View/CMakeLists.txt)
endif(${ANDROID})
