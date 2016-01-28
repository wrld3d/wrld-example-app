set(headers ${headers} ../src/InitialExperience/SdkModel
)
set(currsources
  ../src/InitialExperience/SdkModel/CMakeLists.txt
  ../src/InitialExperience/SdkModel/IInitialExperienceController.h
  ../src/InitialExperience/SdkModel/IInitialExperienceModel.h
  ../src/InitialExperience/SdkModel/IInitialExperienceModule.h
  ../src/InitialExperience/SdkModel/IInitialExperienceStep.h
  ../src/InitialExperience/SdkModel/InitialExperience.h
  ../src/InitialExperience/SdkModel/InitialExperienceController.cpp
  ../src/InitialExperience/SdkModel/InitialExperienceController.h
  ../src/InitialExperience/SdkModel/InitialExperienceIntroStep.cpp
  ../src/InitialExperience/SdkModel/InitialExperienceIntroStep.h
  ../src/InitialExperience/SdkModel/InitialExperienceModel.cpp
  ../src/InitialExperience/SdkModel/InitialExperienceModel.h
  ../src/InitialExperience/SdkModel/InitialExperienceModuleBase.cpp
  ../src/InitialExperience/SdkModel/InitialExperienceModuleBase.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InitialExperience\\SdkModel FILES ${currsources})
