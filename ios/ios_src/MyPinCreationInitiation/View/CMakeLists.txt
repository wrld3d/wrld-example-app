if(${IOS})
set(headers ${headers} ios_src/MyPinCreationInitiation/View
)
set(currsources
  ios_src/MyPinCreationInitiation/View/CMakeLists.txt
  ios_src/MyPinCreationInitiation/View/IMyPinCreationInitiationViewModule.h
  ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationView.h
  ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationView.mm
  ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationViewIncludes.h
  ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationViewInterop.h
  ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationViewInterop.mm
  ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationViewModule.h
  ios_src/MyPinCreationInitiation/View/MyPinCreationInitiationViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\MyPinCreationInitiation\\View FILES ${currsources})
endif(${IOS})
