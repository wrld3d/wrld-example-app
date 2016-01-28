set(headers ${headers} ../src/ScreenControl/View
)
set(currsources
  ../src/ScreenControl/View/ApplyScreenControl.cpp
  ../src/ScreenControl/View/ApplyScreenControl.h
  ../src/ScreenControl/View/CMakeLists.txt
  ../src/ScreenControl/View/IScreenControlView.h
  ../src/ScreenControl/View/IScreenControlViewModel.h
  ../src/ScreenControl/View/ScreenControlViewModelBase.cpp
  ../src/ScreenControl/View/ScreenControlViewModelBase.h
  ../src/ScreenControl/View/ScreenControlViewModelIncludes.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\ScreenControl\\View FILES ${currsources})
