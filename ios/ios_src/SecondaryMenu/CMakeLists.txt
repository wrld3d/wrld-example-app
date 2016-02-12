if(${IOS})
set(headers ${headers} ios_src/SecondaryMenu
)
set(currsources
  ios_src/SecondaryMenu/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SecondaryMenu FILES ${currsources})
include(ios_src/SecondaryMenu/View/CMakeLists.txt)
endif(${IOS})
