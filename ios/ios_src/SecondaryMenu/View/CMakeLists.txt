if(${IOS})
set(headers ${headers} ios_src/SecondaryMenu/View
)
set(currsources
  ios_src/SecondaryMenu/View/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SecondaryMenu\\View FILES ${currsources})
endif(${IOS})
