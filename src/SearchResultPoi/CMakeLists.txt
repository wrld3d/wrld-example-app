set(headers ${headers} ../src/SearchResultPoi
)
set(currsources
  ../src/SearchResultPoi/CMakeLists.txt
  ../src/SearchResultPoi/SearchResultPoi.h
  ../src/SearchResultPoi/SearchResultPoiPinToggledMessage.cpp
  ../src/SearchResultPoi/SearchResultPoiPinToggledMessage.h
  ../src/SearchResultPoi/SearchResultPoiViewImageDownloadCompletedMessage.cpp
  ../src/SearchResultPoi/SearchResultPoiViewImageDownloadCompletedMessage.h
  ../src/SearchResultPoi/SearchResultPoiViewOpenedMessage.cpp
  ../src/SearchResultPoi/SearchResultPoiViewOpenedMessage.h
  ../src/SearchResultPoi/SearchResultPoiViewClosedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchResultPoi FILES ${currsources})
include(../src/SearchResultPoi/SdkModel/CMakeLists.txt)
include(../src/SearchResultPoi/View/CMakeLists.txt)
