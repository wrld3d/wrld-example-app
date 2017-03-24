if(${ANDROID})
set(headers ${headers} jni/InitialExperience/Preload
)
set(currsources
  jni/InitialExperience/Preload/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InitialExperience\\Preload FILES ${currsources})
include(jni/InitialExperience/Preload/SdkModel/CMakeLists.txt)
endif(${ANDROID})
