if(${ANDROID})
set(headers ${headers} jni/InitialExperience
)
set(currsources
  jni/InitialExperience/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InitialExperience FILES ${currsources})
include(jni/InitialExperience/Preload/SdkModel/CMakeLists.txt)
include(jni/InitialExperience/SdkModel/CMakeLists.txt)
include(jni/InitialExperience/View/CMakeLists.txt)
endif(${ANDROID})
