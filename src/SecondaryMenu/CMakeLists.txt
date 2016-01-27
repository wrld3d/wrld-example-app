set(headers ${headers} src/SecondaryMenu
)
set(currsources
  src/SecondaryMenu/PerformedSearchMessage.cpp
  src/SecondaryMenu/PerformedSearchMessage.h
  src/SecondaryMenu/SecondaryMenu.h
)
set(sources ${sources} ${currsources})
source_group(\\SecondaryMenu FILES ${currsources})
include(src/SecondaryMenu/SdkModel/CMakeLists.txt)
include(src/SecondaryMenu/View/CMakeLists.txt)
