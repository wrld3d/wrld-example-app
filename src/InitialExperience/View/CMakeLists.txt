set(headers ${headers} src/InitialExperience/View
)
set(currsources
  src/InitialExperience/View/IInitialExperienceIntroView.h
  src/InitialExperience/View/InitialExperienceIntroController.cpp
  src/InitialExperience/View/InitialExperienceIntroController.h
)
set(sources ${sources} ${currsources})
source_group(\\InitialExperience\\View FILES ${currsources})
