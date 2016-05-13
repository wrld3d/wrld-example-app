set(headers ${headers} ../src/Search/Lax/SdkModel
)
set(currsources
  ../src/Search/Lax/SdkModel/ILaxSearchMenuModule.h
  ../src/Search/Lax/SdkModel/LaxOfficeResultMenuOptionSelectedMessageHandler.cpp
  ../src/Search/Lax/SdkModel/LaxOfficeResultMenuOptionSelectedMessageHandler.h
  ../src/Search/Lax/SdkModel/LaxSearchMenuModule.cpp
  ../src/Search/Lax/SdkModel/LaxSearchMenuModule.h
  ../src/Search/Lax/SdkModel/LaxSearchService.cpp
  ../src/Search/Lax/SdkModel/LaxSearchService.h
  ../src/Search/Lax/SdkModel/LaxSearchServiceModule.cpp
  ../src/Search/Lax/SdkModel/LaxSearchServiceModule.h
  ../src/Search/Lax/SdkModel/LaxSearchTransitionPinController.cpp
  ../src/Search/Lax/SdkModel/LaxSearchTransitionPinController.h
  ../src/Search/Lax/SdkModel/LaxSearchTransitionPinSelectionHandler.cpp
  ../src/Search/Lax/SdkModel/LaxSearchTransitionPinSelectionHandler.h
  ../src/Search/Lax/SdkModel/LaxTransitionResultModel.cpp
  ../src/Search/Lax/SdkModel/LaxTransitionResultModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Lax\\SdkModel FILES ${currsources})
include(../src/Search/Lax/SdkModel/SearchParser/CMakeLists.txt)
