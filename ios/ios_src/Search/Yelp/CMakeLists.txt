if(${IOS})
set(headers ${headers} ios_src/Search/Yelp
)
set(currsources
  ios_src/Search/Yelp/CMakeLists.txt
  ios_src/Search/Yelp/iOSYelpBusinessQuery.h
  ios_src/Search/Yelp/iOSYelpBusinessQuery.mm
  ios_src/Search/Yelp/iOSYelpSearchQuery.h
  ios_src/Search/Yelp/iOSYelpSearchQuery.mm
  ios_src/Search/Yelp/iOSYelpSearchQueryFactory.h
  ios_src/Search/Yelp/iOSYelpSearchQueryFactory.mm
  ios_src/Search/Yelp/iOSYelpSearchServiceModule.cpp
  ios_src/Search/Yelp/iOSYelpSearchServiceModule.h
  ios_src/Search/Yelp/NSURLRequest+OAuth.h
  ios_src/Search/Yelp/NSURLRequest+OAuth.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Search\\Yelp FILES ${currsources})
include(ios_src/Search/Yelp/OAuthConsumer/CMakeLists.txt)
endif(${IOS})
