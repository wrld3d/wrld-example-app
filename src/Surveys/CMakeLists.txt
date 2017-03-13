set(headers ${headers} ../src/Surveys
)
set(currsources
  ../src/Surveys/CMakeLists.txt
  ../src/Surveys/StartUxSurveyMessage.h
  ../src/Surveys/SurveyTimeRequirementMetMessage.h
  ../src/Surveys/Surveys.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Surveys FILES ${currsources})
include(../src/Surveys/SdkModel/CMakeLists.txt)
