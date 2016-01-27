if(${IOS})
set(headers ${headers} ios/ios_src/MyPinCreationDetails/View
)
set(currsources
  ios/ios_src/MyPinCreationDetails/View/IMyPinCreationDetailsViewModule.h
  ios/ios_src/MyPinCreationDetails/View/MyPinCreationDetailsView.h
  ios/ios_src/MyPinCreationDetails/View/MyPinCreationDetailsView.mm
  ios/ios_src/MyPinCreationDetails/View/MyPinCreationDetailsViewIncludes.h
  ios/ios_src/MyPinCreationDetails/View/MyPinCreationDetailsViewInterop.h
  ios/ios_src/MyPinCreationDetails/View/MyPinCreationDetailsViewInterop.mm
  ios/ios_src/MyPinCreationDetails/View/MyPinCreationDetailsViewModule.h
  ios/ios_src/MyPinCreationDetails/View/MyPinCreationDetailsViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\MyPinCreationDetails\\View FILES ${currsources})
endif(${IOS})
