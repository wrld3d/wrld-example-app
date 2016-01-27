if(${IOS})
set(headers ${headers} ios/ios_src/InitialExperience
)
set(currsources
  ios/ios_src/InitialExperience/iOSInitialExperienceModule.cpp
  ios/ios_src/InitialExperience/iOSInitialExperienceModule.h
)
set(sources ${sources} ${currsources})
source_group(\\_src\\InitialExperience FILES ${currsources})
include(ios/ios_src/InitialExperience/Preload/CMakeLists.txt)
include(ios/ios_src/InitialExperience/View/CMakeLists.txt)
endif(${IOS})
