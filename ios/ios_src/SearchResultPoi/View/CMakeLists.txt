if(${IOS})
set(headers ${headers} ios_src/SearchResultPoi/View
)
set(currsources
  ios_src/SearchResultPoi/View/CMakeLists.txt
  ios_src/SearchResultPoi/View/ExampleTourSearchResultPoiView.h
  ios_src/SearchResultPoi/View/ExampleTourSearchResultPoiView.mm
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
  ios_src/SearchResultPoi/View/SwallowDepartmentSearchResultPoiView.h
  ios_src/SearchResultPoi/View/SwallowDepartmentSearchResultPoiView.mm
  ios_src/SearchResultPoi/View/SwallowFacilitySearchResultPoiView.h
  ios_src/SearchResultPoi/View/SwallowFacilitySearchResultPoiView.mm
  ios_src/SearchResultPoi/View/SwallowMeetingRoomSearchResultPoiView.h
  ios_src/SearchResultPoi/View/SwallowMeetingRoomSearchResultPoiView.mm
  ios_src/SearchResultPoi/View/SwallowPersonSearchResultPoiView.h
  ios_src/SearchResultPoi/View/SwallowPersonSearchResultPoiView.mm
  ios_src/SearchResultPoi/View/SwallowWorkingGroupSearchResultPoiView.h
  ios_src/SearchResultPoi/View/SwallowWorkingGroupSearchResultPoiView.mm
  ios_src/SearchResultPoi/View/YelpSearchResultPoiView.h
  ios_src/SearchResultPoi/View/YelpSearchResultPoiView.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchResultPoi\\View FILES ${currsources})
endif(${IOS})
