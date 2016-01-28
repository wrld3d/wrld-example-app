if(${IOS})
set(headers ${headers} ios_src/FlattenButton/View
)
set(currsources
  ios_src/FlattenButton/View/CMakeLists.txt
  ios_src/FlattenButton/View/FlattenButtonView.h
  ios_src/FlattenButton/View/FlattenButtonView.mm
  ios_src/FlattenButton/View/FlattenButtonViewIncludes.h
  ios_src/FlattenButton/View/FlattenButtonViewInterop.h
  ios_src/FlattenButton/View/FlattenButtonViewInterop.mm
  ios_src/FlattenButton/View/FlattenButtonViewModule.h
  ios_src/FlattenButton/View/FlattenButtonViewModule.mm
  ios_src/FlattenButton/View/IFlattenButtonViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\FlattenButton\\View FILES ${currsources})
endif(${IOS})
