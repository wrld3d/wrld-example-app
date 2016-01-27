if(${IOS})
set(headers ${headers} ios/ios_src/Search/Yelp
)
set(currsources
  ios/ios_src/Search/Yelp/iOSYelpBusinessQuery.h
  ios/ios_src/Search/Yelp/iOSYelpBusinessQuery.mm
  ios/ios_src/Search/Yelp/iOSYelpSearchQuery.h
  ios/ios_src/Search/Yelp/iOSYelpSearchQuery.mm
  ios/ios_src/Search/Yelp/iOSYelpSearchQueryFactory.h
  ios/ios_src/Search/Yelp/iOSYelpSearchQueryFactory.mm
  ios/ios_src/Search/Yelp/iOSYelpSearchServiceModule.cpp
  ios/ios_src/Search/Yelp/iOSYelpSearchServiceModule.h
  ios/ios_src/Search/Yelp/NSURLRequest+OAuth.h
  ios/ios_src/Search/Yelp/NSURLRequest+OAuth.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Search\\Yelp FILES ${currsources})
include(ios/ios_src/Search/Yelp/OAuthConsumer/CMakeLists.txt)
endif(${IOS})
