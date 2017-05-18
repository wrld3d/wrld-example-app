if(${IOS})
set(headers ${headers} ios_src/SearchMenu/View
)
set(currsources
  ios_src/SearchMenu/View/ISearchMenuViewModule.h
  ios_src/SearchMenu/View/SearchMenuDragTab.h
  ios_src/SearchMenu/View/SearchMenuDragTab.mm
  ios_src/SearchMenu/View/SearchMenuInputDelegate.h
  ios_src/SearchMenu/View/SearchMenuInputDelegate.mm
  ios_src/SearchMenu/View/SearchMenuResultsSpinner.h
  ios_src/SearchMenu/View/SearchMenuResultsSpinner.mm
  ios_src/SearchMenu/View/SearchMenuView.h
  ios_src/SearchMenu/View/SearchMenuView.mm
  ios_src/SearchMenu/View/SearchMenuViewIncludes.h
  ios_src/SearchMenu/View/SearchMenuViewInterop.h
  ios_src/SearchMenu/View/SearchMenuViewModule.h
  ios_src/SearchMenu/View/SearchMenuViewModule.mm
  ios_src/SearchMenu/View/SearchResultsTableDataProvider.h
  ios_src/SearchMenu/View/SearchResultsTableDataProvider.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchMenu\\View FILES ${currsources})
endif(${IOS})
