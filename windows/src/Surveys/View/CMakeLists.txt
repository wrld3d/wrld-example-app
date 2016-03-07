set(headers ${headers} src/Surveys/View
)
set(currsources
  src/Surveys/View/ISurveyViewModule.h
  src/Surveys/View/SurveyViewModule.cpp
  src/Surveys/View/SurveyViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
 
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Surveys\\View FILES ${currsources})
