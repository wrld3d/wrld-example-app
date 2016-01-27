if(${IOS})
set(headers ${headers} ios/ios_src/SearchResultMenu/View
)
set(currsources
  ios/ios_src/SearchResultMenu/View/ISearchResultMenuViewModule.h
  ios/ios_src/SearchResultMenu/View/SearchResultMenuDataProvider.h
  ios/ios_src/SearchResultMenu/View/SearchResultMenuDataProvider.mm
  ios/ios_src/SearchResultMenu/View/SearchResultMenuView.h
  ios/ios_src/SearchResultMenu/View/SearchResultMenuView.mm
  ios/ios_src/SearchResultMenu/View/SearchResultMenuViewIncludes.h
  ios/ios_src/SearchResultMenu/View/SearchResultMenuViewInterop.mm
  ios/ios_src/SearchResultMenu/View/SearchResultMenuViewInterop.h
  ios/ios_src/SearchResultMenu/View/SearchResultMenuViewModule.h
  ios/ios_src/SearchResultMenu/View/SearchResultMenuViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\SearchResultMenu\\View FILES ${currsources})
endif(${IOS})
