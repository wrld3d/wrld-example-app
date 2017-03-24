if(${ANDROID})
set(headers ${headers} jni/InteriorsPosition/SdkModel
)
set(currsources
  jni/InteriorsPosition/SdkModel/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InteriorsPosition\\SdkModel FILES ${currsources})
include(jni/InteriorsPosition/SdkModel/IndoorAtlas/CMakeLists.txt)
include(jni/InteriorsPosition/SdkModel/SenionLab/CMakeLists.txt)
endif(${ANDROID})
