set(headers ${headers} src/InitialExperience/SdkModel
)
set(currsources
  src/InitialExperience/SdkModel/WindowsInitialExperienceModule.cpp
  src/InitialExperience/SdkModel/WindowsInitialExperienceModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "/clr /EHa")

set(sources ${sources} ${currsources})
source_group(\\InitialExperience\\SdkModel FILES ${currsources})
