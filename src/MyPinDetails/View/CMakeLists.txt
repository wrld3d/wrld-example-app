set(headers ${headers} ../src/MyPinDetails/View
)
set(currsources
  ../src/MyPinDetails/View/CMakeLists.txt
  ../src/MyPinDetails/View/IMyPinDetailsDisplayService.h
  ../src/MyPinDetails/View/IMyPinDetailsView.h
  ../src/MyPinDetails/View/IMyPinDetailsViewModel.h
  ../src/MyPinDetails/View/MyPinDetailsController.cpp
  ../src/MyPinDetails/View/MyPinDetailsController.h
  ../src/MyPinDetails/View/MyPinDetailsDisplayService.cpp
  ../src/MyPinDetails/View/MyPinDetailsDisplayService.h
  ../src/MyPinDetails/View/MyPinDetailsModelSelectedObserver.cpp
  ../src/MyPinDetails/View/MyPinDetailsModelSelectedObserver.h
  ../src/MyPinDetails/View/MyPinDetailsOpenableControl.cpp
  ../src/MyPinDetails/View/MyPinDetailsOpenableControl.h
  ../src/MyPinDetails/View/MyPinDetailsViewModel.cpp
  ../src/MyPinDetails/View/MyPinDetailsViewModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MyPinDetails\\View FILES ${currsources})
