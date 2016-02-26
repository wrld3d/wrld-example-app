set(headers ${headers} ../src/Surveys/SdkModel
)
set(currsources
  ../src/Surveys/SdkModel/CMakeLists.txt
  ../src/Surveys/SdkModel/ISurveyModule.h
  ../src/Surveys/SdkModel/SurveyModule.cpp
  ../src/Surveys/SdkModel/SurveyModule.h
  ../src/Surveys/SdkModel/SurveyObserver.cpp
  ../src/Surveys/SdkModel/SurveyObserver.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Surveys\\SdkModel FILES ${currsources})
