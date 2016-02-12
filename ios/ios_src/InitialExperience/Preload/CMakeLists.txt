if(${IOS})
set(headers ${headers} ios_src/InitialExperience/Preload
)
set(currsources
  ios_src/InitialExperience/Preload/CMakeLists.txt
  ios_src/InitialExperience/Preload/iOSInitialExperiencePreLoadModel.h
  ios_src/InitialExperience/Preload/iOSInitialExperiencePreLoadModel.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\InitialExperience\\Preload FILES ${currsources})
endif(${IOS})
