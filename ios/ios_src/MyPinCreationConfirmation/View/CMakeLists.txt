if(${IOS})
set(headers ${headers} ios/ios_src/MyPinCreationConfirmation/View
)
set(currsources
  ios/ios_src/MyPinCreationConfirmation/View/IMyPinCreationConfirmationViewModule.h
  ios/ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationView.h
  ios/ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationView.mm
  ios/ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationViewIncludes.h
  ios/ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationViewInterop.h
  ios/ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationViewInterop.mm
  ios/ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationViewModule.h
  ios/ios_src/MyPinCreationConfirmation/View/MyPinCreationConfirmationViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\MyPinCreationConfirmation\\View FILES ${currsources})
endif(${IOS})
