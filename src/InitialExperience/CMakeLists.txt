set(headers ${headers} src/InitialExperience
)
set(currsources
  src/InitialExperience/InitialExperienceIntroDismissedMessage.h
  src/InitialExperience/ShowInitialExperienceIntroMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\InitialExperience FILES ${currsources})
include(src/InitialExperience/Preload/CMakeLists.txt)
include(src/InitialExperience/SdkModel/CMakeLists.txt)
include(src/InitialExperience/SearchAttract/CMakeLists.txt)
include(src/InitialExperience/View/CMakeLists.txt)
