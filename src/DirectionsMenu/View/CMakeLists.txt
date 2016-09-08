set(headers ${headers} ../src/DirectionsMenu/View
)
set(currsources
  ../src/DirectionsMenu/View/CMakeLists.txt
  ../src/DirectionsMenu/View/DirectionsMenuController.cpp  ../src/DirectionsMenu/View/DirectionsMenuController.h  ../src/DirectionsMenu/View/IDirectionsMenuView.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\DirectionsMenu\\View FILES ${currsources})