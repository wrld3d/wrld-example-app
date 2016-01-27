if(${IOS})
set(headers ${headers} ios/ios_src/MyPinCreationInitiation/View
)
set(currsources
  ios/ios_src/MyPinCreationInitiation/View/IMyPinCreationInitiationViewModule.h
  ios/ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationView.h
  ios/ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationView.mm
  ios/ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationViewIncludes.h
  ios/ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationViewInterop.h
  ios/ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationViewInterop.mm
  ios/ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationViewModule.h
  ios/ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\MyPinCreationInitiation\\View FILES ${currsources})
endif(${IOS})
