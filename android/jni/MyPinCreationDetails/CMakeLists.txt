if(${ANDROID})
set(headers ${headers} jni/MyPinCreationDetails
)
set(currsources
  jni/MyPinCreationDetails/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\MyPinCreationDetails FILES ${currsources})
include(jni/MyPinCreationDetails/View/CMakeLists.txt)
endif(${ANDROID})
