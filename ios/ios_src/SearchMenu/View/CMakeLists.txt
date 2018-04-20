if(${IOS})
set(headers ${headers} ios_src/SearchMenu/View
)
set(currsources
  ios_src/SearchMenu/View/CMakeLists.txt
  ios_src/SearchMenu/View/SearchWidgetMenuContext.mm
  ios_src/SearchMenu/View/SearchWidgetMenuContext.h
  ios_src/SearchMenu/View/SearchWidgetView.mm
  ios_src/SearchMenu/View/SearchWidgetView.h
  ios_src/SearchMenu/View/SearchWidgetContainerView.mm
  ios_src/SearchMenu/View/SearchWidgetContainerView.h
  ios_src/SearchMenu/View/WidgetSearchResultTableViewCell.mm
  ios_src/SearchMenu/View/WidgetSearchResultTableViewCell.h
  ios_src/SearchMenu/View/SearchWidgetViewIncludes.h
  ios_src/SearchMenu/View/ISearchWidgetViewModule.h
  ios_src/SearchMenu/View/SearchWidgetViewModule.h
  ios_src/SearchMenu/View/SearchWidgetViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchMenu\\View FILES ${currsources})
endif(${IOS})
