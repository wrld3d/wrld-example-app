if(${IOS})
set(headers ${headers} ios_src/InitialExperience/View
)
set(currsources
  ios_src/InitialExperience/View/CMakeLists.txt
  ios_src/InitialExperience/View/IInitialExperienceIntroViewModule.h
  ios_src/InitialExperience/View/InitialExperienceIntroBackgroundView.h
  ios_src/InitialExperience/View/InitialExperienceIntroBackgroundView.mm
  ios_src/InitialExperience/View/InitialExperienceIntroView.h
  ios_src/InitialExperience/View/InitialExperienceIntroView.mm
  ios_src/InitialExperience/View/InitialExperienceIntroViewIncludes.h
  ios_src/InitialExperience/View/InitialExperienceIntroViewInterop.h
  ios_src/InitialExperience/View/InitialExperienceIntroViewInterop.mm
  ios_src/InitialExperience/View/InitialExperienceIntroViewModule.h
  ios_src/InitialExperience/View/InitialExperienceIntroViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\InitialExperience\\View FILES ${currsources})
endif(${IOS})
