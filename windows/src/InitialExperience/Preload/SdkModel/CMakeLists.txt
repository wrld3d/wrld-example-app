set(headers ${headers} src/InitialExperience/Preload/SdkModel
)
set(currsources
  src/InitialExperience/Preload/SdkModel/WindowsInitialExperiencePreLoadModel.cpp
  src/InitialExperience/Preload/SdkModel/WindowsInitialExperiencePreLoadModel.h
)

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\InitialExperience\\Preload\\SdkModel FILES ${currsources})
