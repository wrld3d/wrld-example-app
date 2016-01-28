if(${IOS})
set(headers ${headers} ios_src/InitialExperience
)
set(currsources
  ios_src/InitialExperience/CMakeLists.txt
  ios_src/InitialExperience/iOSInitialExperienceModule.cpp
  ios_src/InitialExperience/iOSInitialExperienceModule.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\InitialExperience FILES ${currsources})
include(ios_src/InitialExperience/Preload/CMakeLists.txt)
include(ios_src/InitialExperience/View/CMakeLists.txt)
endif(${IOS})
