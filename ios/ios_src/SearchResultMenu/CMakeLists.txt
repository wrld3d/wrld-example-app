if(${IOS})
set(headers ${headers} ios/ios_src/SearchResultMenu
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\SearchResultMenu FILES ${currsources})
include(ios/ios_src/SearchResultMenu/View/CMakeLists.txt)
endif(${IOS})
