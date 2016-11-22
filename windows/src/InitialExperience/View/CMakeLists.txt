set(headers ${headers} src/InitialExperience/View
)
set(currsources
  src/InitialExperience/View/InitialExperienceIntroView.cpp
  src/InitialExperience/View/InitialExperienceIntroView.h
  src/InitialExperience/View/InitialExperienceIntroViewModule.cpp
  src/InitialExperience/View/InitialExperienceIntroViewModule.h
  src/InitialExperience/View/InitialExperienceViewIncludes.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\InitialExperience\\View FILES ${currsources})
