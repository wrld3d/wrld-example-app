set(headers ${headers} ../src/ViewControllerUpdater/View
)
set(currsources
  ../src/ViewControllerUpdater/View/CMakeLists.txt
  ../src/ViewControllerUpdater/View/IUpdateableViewController.h
  ../src/ViewControllerUpdater/View/IViewControllerUpdaterModel.h
  ../src/ViewControllerUpdater/View/IViewControllerUpdaterModule.h
  ../src/ViewControllerUpdater/View/ViewControllerUpdater.h
  ../src/ViewControllerUpdater/View/ViewControllerUpdaterModel.cpp
  ../src/ViewControllerUpdater/View/ViewControllerUpdaterModel.h
  ../src/ViewControllerUpdater/View/ViewControllerUpdaterModule.cpp
  ../src/ViewControllerUpdater/View/ViewControllerUpdaterModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\ViewControllerUpdater\\View FILES ${currsources})
