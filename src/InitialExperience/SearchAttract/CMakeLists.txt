set(headers ${headers} src/InitialExperience/SearchAttract
)
set(currsources
  src/InitialExperience/SearchAttract/InitialExperienceSearchResultAttractModeModelStateEnteredMessage.h
  src/InitialExperience/SearchAttract/InitialExperienceSearchResultAttractModeModelStateExitedMessage.h
  src/InitialExperience/SearchAttract/InitialExperienceSearchResultAttractModeModelStateUpdatedMessage.h
  src/InitialExperience/SearchAttract/InitialExperienceSearchResultAttractModeModule.cpp
  src/InitialExperience/SearchAttract/InitialExperienceSearchResultAttractModeModule.h
)
set(sources ${sources} ${currsources})
source_group(\\InitialExperience\\SearchAttract FILES ${currsources})
include(src/InitialExperience/SearchAttract/SdkModel/CMakeLists.txt)
include(src/InitialExperience/SearchAttract/View/CMakeLists.txt)
