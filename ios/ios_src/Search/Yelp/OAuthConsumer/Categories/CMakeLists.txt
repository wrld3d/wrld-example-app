if(${IOS})
set(headers ${headers} ios_src/Search/Yelp/OAuthConsumer/Categories
)
set(currsources
  ios_src/Search/Yelp/OAuthConsumer/Categories/CMakeLists.txt
  ios_src/Search/Yelp/OAuthConsumer/Categories/NSMutableURLRequest+Parameters.h
  ios_src/Search/Yelp/OAuthConsumer/Categories/NSMutableURLRequest+Parameters.m
  ios_src/Search/Yelp/OAuthConsumer/Categories/NSString+URLEncoding.h
  ios_src/Search/Yelp/OAuthConsumer/Categories/NSString+URLEncoding.m
  ios_src/Search/Yelp/OAuthConsumer/Categories/NSURL+Base.h
  ios_src/Search/Yelp/OAuthConsumer/Categories/NSURL+Base.m
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-w")

set(sources ${sources} ${currsources})
source_group(\\ios_src\\Search\\Yelp\\OAuthConsumer\\Categories FILES ${currsources})
endif(${IOS})
