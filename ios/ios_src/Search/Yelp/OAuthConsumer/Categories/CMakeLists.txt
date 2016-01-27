if(${IOS})
set(headers ${headers} ios/ios_src/Search/Yelp/OAuthConsumer/Categories
)
set(currsources
  ios/ios_src/Search/Yelp/OAuthConsumer/Categories/NSMutableURLRequest+Parameters.h
  ios/ios_src/Search/Yelp/OAuthConsumer/Categories/NSMutableURLRequest+Parameters.m
  ios/ios_src/Search/Yelp/OAuthConsumer/Categories/NSString+URLEncoding.h
  ios/ios_src/Search/Yelp/OAuthConsumer/Categories/NSString+URLEncoding.m
  ios/ios_src/Search/Yelp/OAuthConsumer/Categories/NSURL+Base.h
  ios/ios_src/Search/Yelp/OAuthConsumer/Categories/NSURL+Base.m
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-w")

set(sources ${sources} ${currsources})
source_group(\\_src\\Search\\Yelp\\OAuthConsumer\\Categories FILES ${currsources})
endif(${IOS})
