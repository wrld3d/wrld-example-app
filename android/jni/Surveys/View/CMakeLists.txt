if(${ANDROID})
set(headers ${headers} jni/Surveys/View
)
set(currsources
  jni/Surveys/View/ISurveyViewModule.h
  jni/Surveys/View/SurveyView.h
  jni/Surveys/View/SurveyView.cpp
  jni/Surveys/View/SurveyViewModule.h
  jni/Surveys/View/SurveyViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Surveys\\View FILES ${currsources})
endif(${ANDROID})
