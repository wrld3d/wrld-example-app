if(${IOS})
set(headers ${headers} ios_src/SearchResultPoi/View
)
set(currsources
  ios_src/SearchResultPoi/View/CMakeLists.txt
  ios_src/SearchResultPoi/View/EegeoSearchResultPoiView.h
  ios_src/SearchResultPoi/View/EegeoSearchResultPoiView.mm
  ios_src/SearchResultPoi/View/GeoNamesSearchResultPoiView.h
  ios_src/SearchResultPoi/View/GeoNamesSearchResultPoiView.mm
  ios_src/SearchResultPoi/View/ISearchResultPoiViewModule.h
  ios_src/SearchResultPoi/View/SearchResultPoiView.h
  ios_src/SearchResultPoi/View/SearchResultPoiViewContainer.h
  ios_src/SearchResultPoi/View/SearchResultPoiViewContainer.mm
  ios_src/SearchResultPoi/View/SearchResultPoiViewIncludes.h
  ios_src/SearchResultPoi/View/SearchResultPoiViewInterop.h
  ios_src/SearchResultPoi/View/SearchResultPoiViewInterop.mm
  ios_src/SearchResultPoi/View/SearchResultPoiViewModule.h
  ios_src/SearchResultPoi/View/SearchResultPoiViewModule.mm
  ios_src/SearchResultPoi/View/YelpSearchResultPoiView.h
  ios_src/SearchResultPoi/View/YelpSearchResultPoiView.mm
  ios_src/SearchResultPoi/View/SearchResultPoiSpinner.h
  ios_src/SearchResultPoi/View/SearchResultPoiSpinner.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchResultPoi\\View FILES ${currsources})
endif(${IOS})
