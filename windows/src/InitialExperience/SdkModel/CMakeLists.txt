set(headers ${headers} src/InitialExperience/SdkModel
)
set(currsources
  src/InitialExperience/SdkModel/WindowsInitialExperienceModule.cpp
  src/InitialExperience/SdkModel/WindowsInitialExperienceModule.h
)

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\InitialExperience\\SdkModel FILES ${currsources})
