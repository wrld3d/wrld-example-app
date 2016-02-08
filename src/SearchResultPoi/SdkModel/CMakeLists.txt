set(headers ${headers} ../src/SearchResultPoi/SdkModel
)
set(currsources
  ../src/SearchResultPoi/SdkModel/CMakeLists.txt
  ../src/SearchResultPoi/SdkModel/ISearchResultPoiMyPinService.h
  ../src/SearchResultPoi/SdkModel/ISearchResultPoiViewImageFetcher.h
  ../src/SearchResultPoi/SdkModel/SearchResultPoiMyPinService.cpp
  ../src/SearchResultPoi/SdkModel/SearchResultPoiMyPinService.h
  ../src/SearchResultPoi/SdkModel/SearchResultPoiPinToggledMessageHandler.cpp
  ../src/SearchResultPoi/SdkModel/SearchResultPoiPinToggledMessageHandler.h
  ../src/SearchResultPoi/SdkModel/SearchResultPoiViewImageFetcher.cpp
  ../src/SearchResultPoi/SdkModel/SearchResultPoiViewImageFetcher.h
  ../src/SearchResultPoi/SdkModel/SearchResultPoiViewOpenedMessageHandler.cpp
  ../src/SearchResultPoi/SdkModel/SearchResultPoiViewOpenedMessageHandler.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchResultPoi\\SdkModel FILES ${currsources})
