if(${IOS})
set(headers ${headers} ios/ios_src/Search
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Search FILES ${currsources})
include(ios/ios_src/Search/Yelp/CMakeLists.txt)
endif(${IOS})
