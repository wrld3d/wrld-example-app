set(headers ${headers} ../src/MyPinCreation/View
)
set(currsources
  ../src/MyPinCreation/View/CMakeLists.txt
  ../src/MyPinCreation/View/IMyPinCreationCompositeViewModel.h
  ../src/MyPinCreation/View/IMyPinCreationConfirmationView.h
  ../src/MyPinCreation/View/IMyPinCreationConfirmationViewModel.h
  ../src/MyPinCreation/View/IMyPinCreationInitiationView.h
  ../src/MyPinCreation/View/IMyPinCreationInitiationViewModel.h
  ../src/MyPinCreation/View/MyPinCreationCompositeViewModel.cpp
  ../src/MyPinCreation/View/MyPinCreationCompositeViewModel.h
  ../src/MyPinCreation/View/MyPinCreationConfirmationController.cpp
  ../src/MyPinCreation/View/MyPinCreationConfirmationController.h
  ../src/MyPinCreation/View/MyPinCreationConfirmationOpenableControl.cpp
  ../src/MyPinCreation/View/MyPinCreationConfirmationOpenableControl.h
  ../src/MyPinCreation/View/MyPinCreationConfirmationViewModel.cpp
  ../src/MyPinCreation/View/MyPinCreationConfirmationViewModel.h
  ../src/MyPinCreation/View/MyPinCreationInitiationController.cpp
  ../src/MyPinCreation/View/MyPinCreationInitiationController.h
  ../src/MyPinCreation/View/MyPinCreationInitiationViewModel.cpp
  ../src/MyPinCreation/View/MyPinCreationInitiationViewModel.h
  ../src/MyPinCreation/View/MyPinCreationScreenControl.cpp
  ../src/MyPinCreation/View/MyPinCreationScreenControl.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\MyPinCreation\\View FILES ${currsources})
