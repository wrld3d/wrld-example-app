if(${IOS})
set(headers ${headers} ios/ios_src/InteriorsExplorer/View
)
set(currsources
  ios/ios_src/InteriorsExplorer/View/IInteriorsExplorerViewModule.h
  ios/ios_src/InteriorsExplorer/View/InteriorsExplorerView.h
  ios/ios_src/InteriorsExplorer/View/InteriorsExplorerView.mm
  ios/ios_src/InteriorsExplorer/View/InteriorsExplorerViewIncludes.h
  ios/ios_src/InteriorsExplorer/View/InteriorsExplorerViewInterop.h
  ios/ios_src/InteriorsExplorer/View/InteriorsExplorerViewInterop.mm
  ios/ios_src/InteriorsExplorer/View/InteriorsExplorerViewModule.h
  ios/ios_src/InteriorsExplorer/View/InteriorsExplorerViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\InteriorsExplorer\\View FILES ${currsources})
endif(${IOS})
