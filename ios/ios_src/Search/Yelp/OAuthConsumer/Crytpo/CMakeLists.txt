if(${IOS})
set(headers ${headers} ios/ios_src/Search/Yelp/OAuthConsumer/Crytpo
)
set(currsources
  ios/ios_src/Search/Yelp/OAuthConsumer/Crytpo/Base64Transcoder.c
  ios/ios_src/Search/Yelp/OAuthConsumer/Crytpo/Base64Transcoder.h
  ios/ios_src/Search/Yelp/OAuthConsumer/Crytpo/hmac.c
  ios/ios_src/Search/Yelp/OAuthConsumer/Crytpo/hmac.h
  ios/ios_src/Search/Yelp/OAuthConsumer/Crytpo/sha1.c
  ios/ios_src/Search/Yelp/OAuthConsumer/Crytpo/sha1.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-w")

set(sources ${sources} ${currsources})
source_group(\\_src\\Search\\Yelp\\OAuthConsumer\\Crytpo FILES ${currsources})
endif(${IOS})
