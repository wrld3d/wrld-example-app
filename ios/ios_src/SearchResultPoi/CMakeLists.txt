if(${IOS})
set(headers ${headers} ios_src/SearchResultPoi
)
set(currsources
  ios_src/SearchResultPoi/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchResultPoi FILES ${currsources})
include(ios_src/SearchResultPoi/View/CMakeLists.txt)
endif(${IOS})
