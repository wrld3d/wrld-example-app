set(headers ${headers} src/InteriorsExplorer/View
)
set(currsources
  src/InteriorsExplorer/View/IInteriorsExplorerView.h
  src/InteriorsExplorer/View/InteriorsExplorerController.cpp
  src/InteriorsExplorer/View/InteriorsExplorerController.h
  src/InteriorsExplorer/View/InteriorsExplorerViewModel.cpp
  src/InteriorsExplorer/View/InteriorsExplorerViewModel.h
)
set(sources ${sources} ${currsources})
source_group(\\InteriorsExplorer\\View FILES ${currsources})
