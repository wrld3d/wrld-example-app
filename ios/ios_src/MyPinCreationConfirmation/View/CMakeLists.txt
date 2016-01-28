if(${IOS})
set(headers ${headers} ios_src/MyPinCreationConfirmation/View
)
set(currsources
  ios_src/MyPinCreationConfirmation/View/CMakeLists.txt
  ios_src/MyPinCreationConfirmation/View/IMyPinCreationConfirmationViewModule.h
  ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationView.h
  ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationView.mm
  ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationViewIncludes.h
  ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationViewInterop.h
  ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationViewInterop.mm
  ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationViewModule.h
  ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\MyPinCreationConfirmation\\View FILES ${currsources})
endif(${IOS})
