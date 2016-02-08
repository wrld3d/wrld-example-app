if(${IOS})
set(headers ${headers} ios_src/SecondaryMenu/View
)
set(currsources
  ios_src/SecondaryMenu/View/CMakeLists.txt
  ios_src/SecondaryMenu/View/ISecondaryMenuViewModule.h
  ios_src/SecondaryMenu/View/SecondaryMenuView.h
  ios_src/SecondaryMenu/View/SecondaryMenuView.mm
  ios_src/SecondaryMenu/View/SecondaryMenuViewIncludes.h
  ios_src/SecondaryMenu/View/SecondaryMenuViewInterop.h
  ios_src/SecondaryMenu/View/SecondaryMenuViewModule.h
  ios_src/SecondaryMenu/View/SecondaryMenuViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SecondaryMenu\\View FILES ${currsources})
endif(${IOS})
