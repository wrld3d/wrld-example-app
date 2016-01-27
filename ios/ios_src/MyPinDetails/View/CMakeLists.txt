if(${IOS})
set(headers ${headers} ios/ios_src/MyPinDetails/View
)
set(currsources
  ios/ios_src/MyPinDetails/View/IMyPinDetailsViewModule.h
  ios/ios_src/MyPinDetails/View/MyPinDetailsView.h
  ios/ios_src/MyPinDetails/View/MyPinDetailsView.mm
  ios/ios_src/MyPinDetails/View/MyPinDetailsViewIncludes.h
  ios/ios_src/MyPinDetails/View/MyPinDetailsViewInterop.h
  ios/ios_src/MyPinDetails/View/MyPinDetailsViewInterop.mm
  ios/ios_src/MyPinDetails/View/MyPinDetailsViewModule.h
  ios/ios_src/MyPinDetails/View/MyPinDetailsViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\MyPinDetails\\View FILES ${currsources})
endif(${IOS})
