set(headers ${headers} src/Search/Yelp
)
set(currsources
  src/Search/Yelp/Yelp.h
)
set(sources ${sources} ${currsources})
source_group(\\Search\\Yelp FILES ${currsources})
include(src/Search/Yelp/SdkModel/CMakeLists.txt)
include(src/Search/Yelp/SearchConstants/CMakeLists.txt)
