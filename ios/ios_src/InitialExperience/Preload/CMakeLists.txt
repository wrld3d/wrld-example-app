if(${IOS})
set(headers ${headers} ios/ios_src/InitialExperience/Preload
)
set(currsources
  ios/ios_src/InitialExperience/Preload/iOSInitialExperiencePreLoadModel.h
  ios/ios_src/InitialExperience/Preload/iOSInitialExperiencePreLoadModel.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\InitialExperience\\Preload FILES ${currsources})
endif(${IOS})
