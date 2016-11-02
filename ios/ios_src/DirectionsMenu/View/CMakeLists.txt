set(headers ${headers} ios_src/DirectionsMenu/View
)
set(currsources
  ios_src/DirectionsMenu/View/CMakeLists.txt
  ios_src/DirectionsMenu/View/DirectionsMenuView.h
  ios_src/DirectionsMenu/View/DirectionsMenuView.mm
  ios_src/DirectionsMenu/View/DirectionsMenuViewIncludes.h
  ios_src/DirectionsMenu/View/DirectionsMenuViewModule.h
  ios_src/DirectionsMenu/View/DirectionsMenuViewModule.mm
  ios_src/DirectionsMenu/View/IDirectionsMenuViewModule.h
  ios_src/DirectionsMenu/View/DirectionsMenuWayPointViewCell.h
  ios_src/DirectionsMenu/View/DirectionsMenuWayPointViewCell.m
  ios_src/DirectionsMenu/View/DirectionsMenuStaticView.h
  ios_src/DirectionsMenu/View/DirectionsMenuStaticView.mm
  ios_src/DirectionsMenu/View/DirectionsMenuViewInterop.h
  ios_src/DirectionsMenu/View/DirectionSuggestionTableViewCell.h
  ios_src/DirectionsMenu/View/DirectionSuggestionTableViewCell.m
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\DirectionsMenu\\View FILES ${currsources})