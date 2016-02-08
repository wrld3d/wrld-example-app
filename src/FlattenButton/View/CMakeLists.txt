set(headers ${headers} ../src/FlattenButton/View
)
set(currsources
  ../src/FlattenButton/View/CMakeLists.txt
  ../src/FlattenButton/View/FlattenButtonController.cpp
  ../src/FlattenButton/View/FlattenButtonController.h
  ../src/FlattenButton/View/FlattenButtonScreenControl.cpp
  ../src/FlattenButton/View/FlattenButtonScreenControl.h
  ../src/FlattenButton/View/FlattenButtonViewModel.cpp
  ../src/FlattenButton/View/FlattenButtonViewModel.h
  ../src/FlattenButton/View/IFlattenButtonView.h
  ../src/FlattenButton/View/IFlattenButtonViewModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\FlattenButton\\View FILES ${currsources})
