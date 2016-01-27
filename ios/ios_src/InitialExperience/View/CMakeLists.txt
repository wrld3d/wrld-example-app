if(${IOS})
set(headers ${headers} ios/ios_src/InitialExperience/View
)
set(currsources
  ios/ios_src/InitialExperience/View/IInitialExperienceIntroViewModule.h
  ios/ios_src/InitialExperience/View/InitialExperienceIntroBackgroundView.h
  ios/ios_src/InitialExperience/View/InitialExperienceIntroBackgroundView.mm
  ios/ios_src/InitialExperience/View/InitialExperienceIntroView.h
  ios/ios_src/InitialExperience/View/InitialExperienceIntroView.mm
  ios/ios_src/InitialExperience/View/InitialExperienceIntroViewIncludes.h
  ios/ios_src/InitialExperience/View/InitialExperienceIntroViewInterop.h
  ios/ios_src/InitialExperience/View/InitialExperienceIntroViewInterop.mm
  ios/ios_src/InitialExperience/View/InitialExperienceIntroViewModule.h
  ios/ios_src/InitialExperience/View/InitialExperienceIntroViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\InitialExperience\\View FILES ${currsources})
endif(${IOS})
