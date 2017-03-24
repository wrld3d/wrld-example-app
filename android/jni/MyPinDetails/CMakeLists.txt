if(${ANDROID})
set(headers ${headers} jni/MyPinDetails
)
set(currsources
  jni/MyPinDetails/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\MyPinDetails FILES ${currsources})
include(jni/MyPinDetails/View/CMakeLists.txt)
endif(${ANDROID})
