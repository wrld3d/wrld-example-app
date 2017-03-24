if(${ANDROID})
set(headers ${headers} jni/InitialExperience/SdkModel
)
set(currsources
  jni/InitialExperience/SdkModel/AndroidInitialExperienceModule.h
  jni/InitialExperience/SdkModel/AndroidInitialExperienceModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InitialExperience\\SdkModel FILES ${currsources})
endif(${ANDROID})
