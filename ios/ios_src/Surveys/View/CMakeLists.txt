if(${IOS})
set(headers ${headers} ios_src/Surveys/View
)
set(currsources
  ios_src/Surveys/View/ISurveyViewModule.h
  ios_src/Surveys/View/SurveyAlertViewHandler.h
  ios_src/Surveys/View/SurveyAlertViewHandler.mm
  ios_src/Surveys/View/SurveyViewIncludes.h
  ios_src/Surveys/View/SurveyViewInterop.h
  ios_src/Surveys/View/SurveyViewInterop.mm
  ios_src/Surveys/View/SurveyViewModule.h
  ios_src/Surveys/View/SurveyViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Surveys\\View FILES ${currsources})
endif(${IOS})
