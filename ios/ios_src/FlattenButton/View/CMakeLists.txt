if(${IOS})
set(headers ${headers} ios/ios_src/FlattenButton/View
)
set(currsources
  ios/ios_src/FlattenButton/View/FlattenButtonView.h
  ios/ios_src/FlattenButton/View/FlattenButtonView.mm
  ios/ios_src/FlattenButton/View/FlattenButtonViewIncludes.h
  ios/ios_src/FlattenButton/View/FlattenButtonViewInterop.h
  ios/ios_src/FlattenButton/View/FlattenButtonViewInterop.mm
  ios/ios_src/FlattenButton/View/FlattenButtonViewModule.h
  ios/ios_src/FlattenButton/View/FlattenButtonViewModule.mm
  ios/ios_src/FlattenButton/View/IFlattenButtonViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\_src\\FlattenButton\\View FILES ${currsources})
endif(${IOS})
