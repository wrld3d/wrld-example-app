if(${IOS})
set(headers ${headers} ios_src/NavRouting/View
)
set(currsources
  ios_src/NavRouting/View/INavWidgetViewModule.h
  ios_src/NavRouting/View/NavSearchContainerView.h
  ios_src/NavRouting/View/NavSearchContainerView.mm
  ios_src/NavRouting/View/NavWidgetSearchController.h
  ios_src/NavRouting/View/NavWidgetSearchController.mm
  ios_src/NavRouting/View/NavWidgetSearchView.h
  ios_src/NavRouting/View/NavWidgetSearchView.mm
  ios_src/NavRouting/View/NavWidgetView.h
  ios_src/NavRouting/View/NavWidgetView.mm
  ios_src/NavRouting/View/NavWidgetViewIncludes.h
  ios_src/NavRouting/View/NavWidgetViewModule.h
  ios_src/NavRouting/View/NavWidgetViewModule.mm
  ios_src/NavRouting/View/NavWidgetLocationSetHandler.h
  ios_src/NavRouting/View/NavWidgetLocationSetHandler.mm
  ios_src/NavRouting/View/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\NavRouting\\View FILES ${currsources})
include(ios_src/NavRouting/View/NavRoutingRerouteDialog/CMakeLists.txt)
include(ios_src/NavRouting/View/NavRoutingCalculatingRoute/CMakeLists.txt)
endif(${IOS})
