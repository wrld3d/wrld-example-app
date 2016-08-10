if(${IOS})
set(headers ${headers} ios_src/InteriorsExplorer/View
)
set(currsources
  ios_src/InteriorsExplorer/View/CMakeLists.txt
  ios_src/InteriorsExplorer/View/IInteriorsExplorerViewModule.h
  ios_src/InteriorsExplorer/View/InteriorsExplorerFloorItemView.h
  ios_src/InteriorsExplorer/View/InteriorsExplorerFloorItemView.mm
  ios_src/InteriorsExplorer/View/InteriorsExplorerView.h
  ios_src/InteriorsExplorer/View/InteriorsExplorerView.mm
  ios_src/InteriorsExplorer/View/InteriorsExplorerTutorialView.h
  ios_src/InteriorsExplorer/View/InteriorsExplorerTutorialView.mm
  ios_src/InteriorsExplorer/View/InteriorsExplorerViewIncludes.h
  ios_src/InteriorsExplorer/View/InteriorsExplorerViewInterop.h
  ios_src/InteriorsExplorer/View/InteriorsExplorerViewInterop.mm
  ios_src/InteriorsExplorer/View/InteriorsExplorerViewModule.h
  ios_src/InteriorsExplorer/View/InteriorsExplorerViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\InteriorsExplorer\\View FILES ${currsources})
endif(${IOS})
