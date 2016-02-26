set(headers ${headers} ../src/SearchMenu/View
)
set(currsources
  ../src/SearchMenu/View/CMakeLists.txt
  ../src/SearchMenu/View/ISearchMenuView.h
  ../src/SearchMenu/View/SearchMenuController.cpp
  ../src/SearchMenu/View/SearchMenuController.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchMenu\\View FILES ${currsources})
