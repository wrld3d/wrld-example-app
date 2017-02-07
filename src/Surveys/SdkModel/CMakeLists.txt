set(headers ${headers} ../src/Surveys/SdkModel
)
set(currsources
  ../src/Surveys/SdkModel/CMakeLists.txt
  ../src/Surveys/SdkModel/ISurveyModule.h
  ../src/Surveys/SdkModel/SurveyModule.cpp
  ../src/Surveys/SdkModel/SurveyModule.h
  ../src/Surveys/SdkModel/SurveyObserver.cpp
  ../src/Surveys/SdkModel/SurveyObserver.h
  ../src/Surveys/SdkModel/SurveyTimer.cpp
  ../src/Surveys/SdkModel/SurveyTimer.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Surveys\\SdkModel FILES ${currsources})
