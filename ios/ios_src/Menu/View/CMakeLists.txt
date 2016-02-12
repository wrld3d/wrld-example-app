if(${IOS})
set(headers ${headers} ios_src/Menu/View
)
set(currsources
  ios_src/Menu/View/CellConstants.h
  ios_src/Menu/View/CMakeLists.txt
  ios_src/Menu/View/CustomTableDataProvider.h
  ios_src/Menu/View/CustomTableDataProvider.mm
  ios_src/Menu/View/CustomTableRowSelectionDelegate.h
  ios_src/Menu/View/CustomTableView.h
  ios_src/Menu/View/CustomTableView.mm
  ios_src/Menu/View/CustomTableViewCell.h
  ios_src/Menu/View/CustomTableViewCell.mm
  ios_src/Menu/View/MenuView.h
  ios_src/Menu/View/MenuView.mm
  ios_src/Menu/View/MenuViewIncludes.h
  ios_src/Menu/View/MenuViewInterop.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Menu\\View FILES ${currsources})
endif(${IOS})
