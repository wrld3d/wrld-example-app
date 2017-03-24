if(${ANDROID})
set(headers ${headers} jni/InitialExperience/View
)
set(currsources
  jni/InitialExperience/View/CMakeLists.txt
  jni/InitialExperience/View/InitialExperienceIntroView.h
  jni/InitialExperience/View/InitialExperienceIntroView.cpp
  jni/InitialExperience/View/InitialExperienceViewIncludes.h
  jni/InitialExperience/View/InitialExperienceIntroJni.h
  jni/InitialExperience/View/InitialExperienceIntroJni.cpp
  jni/InitialExperience/View/InitialExperienceIntroViewModule.h
  jni/InitialExperience/View/InitialExperienceIntroViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InitialExperience\\View FILES ${currsources})
endif(${ANDROID})
