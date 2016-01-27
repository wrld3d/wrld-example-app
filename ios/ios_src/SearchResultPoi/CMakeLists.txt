if(${IOS})
set(headers ${headers} ios/ios_src/SearchResultPoi
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\SearchResultPoi FILES ${currsources})
include(ios/ios_src/SearchResultPoi/View/CMakeLists.txt)
endif(${IOS})
