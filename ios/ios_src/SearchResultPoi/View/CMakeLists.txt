if(${IOS})
set(headers ${headers} ios/ios_src/SearchResultPoi/View
)
set(currsources
  ios/ios_src/SearchResultPoi/View/ExampleTourSearchResultPoiView.h
  ios/ios_src/SearchResultPoi/View/ExampleTourSearchResultPoiView.mm
  ios/ios_src/SearchResultPoi/View/GeoNamesSearchResultPoiView.h
  ios/ios_src/SearchResultPoi/View/GeoNamesSearchResultPoiView.mm
  ios/ios_src/SearchResultPoi/View/ISearchResultPoiViewModule.h
  ios/ios_src/SearchResultPoi/View/SearchResultPoiView.h
  ios/ios_src/SearchResultPoi/View/SearchResultPoiViewContainer.h
  ios/ios_src/SearchResultPoi/View/SearchResultPoiViewContainer.mm
  ios/ios_src/SearchResultPoi/View/SearchResultPoiViewIncludes.h
  ios/ios_src/SearchResultPoi/View/SearchResultPoiViewInterop.h
  ios/ios_src/SearchResultPoi/View/SearchResultPoiViewInterop.mm
  ios/ios_src/SearchResultPoi/View/SearchResultPoiViewModule.h
  ios/ios_src/SearchResultPoi/View/SearchResultPoiViewModule.mm
  ios/ios_src/SearchResultPoi/View/YelpSearchResultPoiView.h
  ios/ios_src/SearchResultPoi/View/YelpSearchResultPoiView.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\SearchResultPoi\\View FILES ${currsources})
endif(${IOS})
