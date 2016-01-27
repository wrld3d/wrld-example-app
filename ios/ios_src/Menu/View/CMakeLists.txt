if(${IOS})
set(headers ${headers} ios/ios_src/Menu/View
)
set(currsources
  ios/ios_src/Menu/View/CellConstants.h
  ios/ios_src/Menu/View/CustomTableDataProvider.h
  ios/ios_src/Menu/View/CustomTableDataProvider.mm
  ios/ios_src/Menu/View/CustomTableView.h
  ios/ios_src/Menu/View/CustomTableView.mm
  ios/ios_src/Menu/View/CustomTableViewCell.h
  ios/ios_src/Menu/View/CustomTableViewCell.mm
  ios/ios_src/Menu/View/MenuView.h
  ios/ios_src/Menu/View/MenuView.mm
  ios/ios_src/Menu/View/MenuViewIncludes.h
  ios/ios_src/Menu/View/MenuViewInterop.h
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Menu\\View FILES ${currsources})
endif(${IOS})
