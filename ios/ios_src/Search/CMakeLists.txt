if(${IOS})
set(headers ${headers} ios_src/Search
)
set(currsources
  ios_src/Search/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Search FILES ${currsources})
include(ios_src/Search/Yelp/CMakeLists.txt)
endif(${IOS})
