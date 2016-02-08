set(headers ${headers} src/SecondaryMenu/View
)
set(currsources
  src/SecondaryMenu/View/SecondaryMenuCLI.cpp
  src/SecondaryMenu/View/SecondaryMenuCLI.h
  src/SecondaryMenu/View/SecondaryMenuJni.h
  src/SecondaryMenu/View/SecondaryMenuView.cpp
  src/SecondaryMenu/View/SecondaryMenuView.h
  src/SecondaryMenu/View/SecondaryMenuViewModule.cpp
  src/SecondaryMenu/View/SecondaryMenuViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "/clr /EHa /Y-")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\SecondaryMenu\\View FILES ${currsources})
