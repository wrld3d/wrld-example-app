set(headers ${headers} ../src/SearchResultPoi/View
)
set(currsources
  ../src/SearchResultPoi/View/CMakeLists.txt
  ../src/SearchResultPoi/View/ISearchResultPoiModule.h
  ../src/SearchResultPoi/View/ISearchResultPoiView.h
  ../src/SearchResultPoi/View/ISearchResultPoiViewModel.h
  ../src/SearchResultPoi/View/SearchResultPoiController.cpp
  ../src/SearchResultPoi/View/SearchResultPoiController.h
  ../src/SearchResultPoi/View/DesktopSearchResultPoiController.cpp
  ../src/SearchResultPoi/View/DesktopSearchResultPoiController.h
  ../src/SearchResultPoi/View/SearchResultPoiModule.cpp
  ../src/SearchResultPoi/View/SearchResultPoiModule.h
  ../src/SearchResultPoi/View/SearchResultPoiOpenableControl.cpp
  ../src/SearchResultPoi/View/SearchResultPoiOpenableControl.h
  ../src/SearchResultPoi/View/SearchResultPoiViewModel.cpp
  ../src/SearchResultPoi/View/SearchResultPoiViewModel.h
  ../src/SearchResultPoi/View/DesktopSearchResultPoiViewModel.cpp
  ../src/SearchResultPoi/View/DesktopSearchResultPoiViewModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchResultPoi\\View FILES ${currsources})
