set(headers ${headers} ../src/InitialExperience/View
)
set(currsources
  ../src/InitialExperience/View/CMakeLists.txt
  ../src/InitialExperience/View/IInitialExperienceIntroView.h
  ../src/InitialExperience/View/InitialExperienceIntroController.cpp
  ../src/InitialExperience/View/InitialExperienceIntroController.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\InitialExperience\\View FILES ${currsources})
