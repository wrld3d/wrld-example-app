set(headers ${headers} ../src/Search/Yelp/SearchConstants
)
set(currsources
  ../src/Search/Yelp/SearchConstants/CMakeLists.txt
  ../src/Search/Yelp/SearchConstants/YelpSearchConstants.cpp
  ../src/Search/Yelp/SearchConstants/YelpSearchConstants.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Yelp\\SearchConstants FILES ${currsources})
