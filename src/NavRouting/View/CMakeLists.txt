set(headers ${headers} ../src/NavRouting/View
)
set(currsources
  ../src/NavRouting/View/INavWidgetView.h
  ../src/NavRouting/View/INavWidgetViewModel.h
  ../src/NavRouting/View/NavUIModule.cpp
  ../src/NavRouting/View/NavUIModule.h
  ../src/NavRouting/View/NavWidgetController.cpp
  ../src/NavRouting/View/NavWidgetController.h
  ../src/NavRouting/View/NavWidgetMenuOption.cpp
  ../src/NavRouting/View/NavWidgetMenuOption.h
  ../src/NavRouting/View/NavWidgetOpenableControl.cpp
  ../src/NavRouting/View/NavWidgetOpenableControl.h
  ../src/NavRouting/View/NavWidgetViewModel.cpp
  ../src/NavRouting/View/NavWidgetViewModel.h
  ../src/NavRouting/View/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\NavRouting\\View FILES ${currsources})
