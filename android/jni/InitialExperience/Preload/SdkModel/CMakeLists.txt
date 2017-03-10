if(${ANDROID})
set(headers ${headers} jni/InitialExperience/Preload/SdkModel
)
set(currsources
  jni/InitialExperience/Preload/SdkModel/CMakeLists.txt
  jni/InitialExperience/Preload/SdkModel/AndroidInitialExperiencePreLoadModel.h
  jni/InitialExperience/Preload/SdkModel/AndroidInitialExperiencePreLoadModel.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InitialExperience\\Preload\\SdkModel FILES ${currsources})
endif(${ANDROID})
