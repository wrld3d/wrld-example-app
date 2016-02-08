if(${IOS})
set(headers ${headers} ios_src/MyPinCreationDetails/View
)
set(currsources
  ios_src/MyPinCreationDetails/View/CMakeLists.txt
  ios_src/MyPinCreationDetails/View/IMyPinCreationDetailsViewModule.h
  ios_src/MyPinCreationDetails/View/MyPinCreationDetailsView.h
  ios_src/MyPinCreationDetails/View/MyPinCreationDetailsView.mm
  ios_src/MyPinCreationDetails/View/MyPinCreationDetailsViewIncludes.h
  ios_src/MyPinCreationDetails/View/MyPinCreationDetailsViewInterop.h
  ios_src/MyPinCreationDetails/View/MyPinCreationDetailsViewInterop.mm
  ios_src/MyPinCreationDetails/View/MyPinCreationDetailsViewModule.h
  ios_src/MyPinCreationDetails/View/MyPinCreationDetailsViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\MyPinCreationDetails\\View FILES ${currsources})
endif(${IOS})
