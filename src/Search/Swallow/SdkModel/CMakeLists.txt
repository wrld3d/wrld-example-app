set(headers ${headers} ../src/Search/Swallow/SdkModel
)
set(currsources
  ../src/Search/Swallow/SdkModel/ISwallowSearchMenuModule.h
  ../src/Search/Swallow/SdkModel/SwallowDepartmentResultModel.cpp
  ../src/Search/Swallow/SdkModel/SwallowDepartmentResultModel.h
  ../src/Search/Swallow/SdkModel/SwallowFacilityResultModel.cpp
  ../src/Search/Swallow/SdkModel/SwallowFacilityResultModel.h
  ../src/Search/Swallow/SdkModel/SwallowMeetingRoomResultModel.cpp
  ../src/Search/Swallow/SdkModel/SwallowMeetingRoomResultModel.h
  ../src/Search/Swallow/SdkModel/SwallowOfficeResultMenuOptionSelectedMessageHandler.cpp
  ../src/Search/Swallow/SdkModel/SwallowOfficeResultMenuOptionSelectedMessageHandler.h
  ../src/Search/Swallow/SdkModel/SwallowOfficeResultModel.cpp
  ../src/Search/Swallow/SdkModel/SwallowOfficeResultModel.h
  ../src/Search/Swallow/SdkModel/SwallowPersonResultModel.cpp
  ../src/Search/Swallow/SdkModel/SwallowPersonResultModel.h
  ../src/Search/Swallow/SdkModel/SwallowSearchMenuModule.cpp
  ../src/Search/Swallow/SdkModel/SwallowSearchMenuModule.h
  ../src/Search/Swallow/SdkModel/SwallowSearchService.cpp
  ../src/Search/Swallow/SdkModel/SwallowSearchService.h
  ../src/Search/Swallow/SdkModel/SwallowSearchServiceModule.cpp
  ../src/Search/Swallow/SdkModel/SwallowSearchServiceModule.h
  ../src/Search/Swallow/SdkModel/SwallowSearchTransitionPinController.cpp
  ../src/Search/Swallow/SdkModel/SwallowSearchTransitionPinController.h
  ../src/Search/Swallow/SdkModel/SwallowSearchTransitionPinSelectionHandler.cpp
  ../src/Search/Swallow/SdkModel/SwallowSearchTransitionPinSelectionHandler.h
  ../src/Search/Swallow/SdkModel/SwallowTransitionResultModel.cpp
  ../src/Search/Swallow/SdkModel/SwallowTransitionResultModel.h
  ../src/Search/Swallow/SdkModel/SwallowWorkingGroupResultModel.cpp
  ../src/Search/Swallow/SdkModel/SwallowWorkingGroupResultModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Swallow\\SdkModel FILES ${currsources})
include(../src/Search/Swallow/SdkModel/SearchParser/CMakeLists.txt)
