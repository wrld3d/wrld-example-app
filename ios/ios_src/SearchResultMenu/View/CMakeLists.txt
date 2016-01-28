if(${IOS})
set(headers ${headers} ios_src/SearchResultMenu/View
)
set(currsources
  ios_src/SearchResultMenu/View/CMakeLists.txt
  ios_src/SearchResultMenu/View/ISearchResultMenuViewModule.h
  ios_src/SearchResultMenu/View/SearchResultMenuDataProvider.h
  ios_src/SearchResultMenu/View/SearchResultMenuDataProvider.mm
  ios_src/SearchResultMenu/View/SearchResultMenuView.h
  ios_src/SearchResultMenu/View/SearchResultMenuView.mm
  ios_src/SearchResultMenu/View/SearchResultMenuViewIncludes.h
  ios_src/SearchResultMenu/View/SearchResultMenuViewInterop.h
  ios_src/SearchResultMenu/View/SearchResultMenuViewInterop.mm
  ios_src/SearchResultMenu/View/SearchResultMenuViewModule.h
  ios_src/SearchResultMenu/View/SearchResultMenuViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchResultMenu\\View FILES ${currsources})
endif(${IOS})
