if(${IOS})
set(headers ${headers} ios_src/SearchResultSection
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchResultSection FILES ${currsources})
include(ios_src/SearchResultSection/View/CMakeLists.txt)
endif(${IOS})
