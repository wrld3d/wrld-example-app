set(headers ${headers} ../src/MyPinCreationDetails/View
)
set(currsources
  ../src/MyPinCreationDetails/View/CMakeLists.txt
  ../src/MyPinCreationDetails/View/IMyPinCreationDetailsModule.h
  ../src/MyPinCreationDetails/View/IMyPinCreationDetailsView.h
  ../src/MyPinCreationDetails/View/IMyPinCreationDetailsViewModel.h
  ../src/MyPinCreationDetails/View/MyPinCreationDetailsController.cpp
  ../src/MyPinCreationDetails/View/MyPinCreationDetailsController.h
  ../src/MyPinCreationDetails/View/MyPinCreationDetailsModule.cpp
  ../src/MyPinCreationDetails/View/MyPinCreationDetailsModule.h
  ../src/MyPinCreationDetails/View/MyPinCreationDetailsOpenableControl.cpp
  ../src/MyPinCreationDetails/View/MyPinCreationDetailsOpenableControl.h
  ../src/MyPinCreationDetails/View/MyPinCreationDetailsViewModel.cpp
  ../src/MyPinCreationDetails/View/MyPinCreationDetailsViewModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MyPinCreationDetails\\View FILES ${currsources})
