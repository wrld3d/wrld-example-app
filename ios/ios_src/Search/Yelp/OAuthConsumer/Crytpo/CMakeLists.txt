if(${IOS})
set(headers ${headers} ios_src/Search/Yelp/OAuthConsumer/Crytpo
)
set(currsources
  ios_src/Search/Yelp/OAuthConsumer/Crytpo/Base64Transcoder.c
  ios_src/Search/Yelp/OAuthConsumer/Crytpo/Base64Transcoder.h
  ios_src/Search/Yelp/OAuthConsumer/Crytpo/CMakeLists.txt
  ios_src/Search/Yelp/OAuthConsumer/Crytpo/hmac.c
  ios_src/Search/Yelp/OAuthConsumer/Crytpo/hmac.h
  ios_src/Search/Yelp/OAuthConsumer/Crytpo/sha1.c
  ios_src/Search/Yelp/OAuthConsumer/Crytpo/sha1.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-w")

set(sources ${sources} ${currsources})
source_group(\\ios_src\\Search\\Yelp\\OAuthConsumer\\Crytpo FILES ${currsources})
endif(${IOS})
