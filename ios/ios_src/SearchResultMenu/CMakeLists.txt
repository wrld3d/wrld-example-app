if(${IOS})
set(headers ${headers} ios_src/SearchResultMenu
)
set(currsources
  ios_src/SearchResultMenu/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchResultMenu FILES ${currsources})
include(ios_src/SearchResultMenu/View/CMakeLists.txt)
endif(${IOS})
