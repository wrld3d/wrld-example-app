set(headers ${headers} ../src/SearchMenu/View
)
set(currsources
  ../src/SearchMenu/View/CMakeLists.txt
  ../src/SearchMenu/View/ISearchMenuView.h
  ../src/SearchMenu/View/SearchMenuController.cpp
  ../src/SearchMenu/View/SearchMenuController.h
  ../src/SearchMenu/View/DesktopSearchMenuController.cpp
  ../src/SearchMenu/View/DesktopSearchMenuController.h
  ../src/SearchMenu/View/ISearchWidgetView.h
  ../src/SearchMenu/View/ISearchProvider.h
  ../src/SearchMenu/View/SearchServices.cpp
  ../src/SearchMenu/View/SearchServices.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchMenu\\View FILES ${currsources})
