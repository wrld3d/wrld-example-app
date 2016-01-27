set(headers ${headers} src/SecondaryMenu/View
)
set(currsources
  src/SecondaryMenu/View/AboutPageMenuOption.cpp
  src/SecondaryMenu/View/AboutPageMenuOption.h
  src/SecondaryMenu/View/ISecondaryMenuView.h
  src/SecondaryMenu/View/OptionsMenuOption.cpp
  src/SecondaryMenu/View/OptionsMenuOption.h
  src/SecondaryMenu/View/SecondaryMenuController.cpp
  src/SecondaryMenu/View/SecondaryMenuController.h
)
set(sources ${sources} ${currsources})
source_group(\\SecondaryMenu\\View FILES ${currsources})
