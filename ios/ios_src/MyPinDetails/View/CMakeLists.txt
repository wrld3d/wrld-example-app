if(${IOS})
set(headers ${headers} ios_src/MyPinDetails/View
)
set(currsources
  ios_src/MyPinDetails/View/CMakeLists.txt
  ios_src/MyPinDetails/View/IMyPinDetailsViewModule.h
  ios_src/MyPinDetails/View/MyPinDetailsView.h
  ios_src/MyPinDetails/View/MyPinDetailsView.mm
  ios_src/MyPinDetails/View/MyPinDetailsViewIncludes.h
  ios_src/MyPinDetails/View/MyPinDetailsViewInterop.h
  ios_src/MyPinDetails/View/MyPinDetailsViewInterop.mm
  ios_src/MyPinDetails/View/MyPinDetailsViewModule.h
  ios_src/MyPinDetails/View/MyPinDetailsViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\MyPinDetails\\View FILES ${currsources})
endif(${IOS})
