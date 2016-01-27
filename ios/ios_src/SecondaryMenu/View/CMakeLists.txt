if(${IOS})
set(headers ${headers} ios/ios_src/SecondaryMenu/View
)
set(currsources
  ios/ios_src/SecondaryMenu/View/ISecondaryMenuViewModule.h
  ios/ios_src/SecondaryMenu/View/SecondaryMenuView.h
  ios/ios_src/SecondaryMenu/View/SecondaryMenuView.mm
  ios/ios_src/SecondaryMenu/View/SecondaryMenuViewIncludes.h
  ios/ios_src/SecondaryMenu/View/SecondaryMenuViewInterop.h
  ios/ios_src/SecondaryMenu/View/SecondaryMenuViewModule.h
  ios/ios_src/SecondaryMenu/View/SecondaryMenuViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\SecondaryMenu\\View FILES ${currsources})
endif(${IOS})
