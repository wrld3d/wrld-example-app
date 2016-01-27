if(${IOS})
set(headers ${headers} ios/ios_src/Search/Yelp/OAuthConsumer
)
set(currsources
  ios/ios_src/Search/Yelp/OAuthConsumer/OACall.h
  ios/ios_src/Search/Yelp/OAuthConsumer/OACall.m
  ios/ios_src/Search/Yelp/OAuthConsumer/OAConsumer.h
  ios/ios_src/Search/Yelp/OAuthConsumer/OAConsumer.m
  ios/ios_src/Search/Yelp/OAuthConsumer/OADataFetcher.h
  ios/ios_src/Search/Yelp/OAuthConsumer/OADataFetcher.m
  ios/ios_src/Search/Yelp/OAuthConsumer/OAHMAC_SHA1SignatureProvider.h
  ios/ios_src/Search/Yelp/OAuthConsumer/OAHMAC_SHA1SignatureProvider.m
  ios/ios_src/Search/Yelp/OAuthConsumer/OAMutableURLRequest.h
  ios/ios_src/Search/Yelp/OAuthConsumer/OAMutableURLRequest.m
  ios/ios_src/Search/Yelp/OAuthConsumer/OAPlaintextSignatureProvider.h
  ios/ios_src/Search/Yelp/OAuthConsumer/OAPlaintextSignatureProvider.m
  ios/ios_src/Search/Yelp/OAuthConsumer/OAProblem.h
  ios/ios_src/Search/Yelp/OAuthConsumer/OAProblem.m
  ios/ios_src/Search/Yelp/OAuthConsumer/OARequestParameter.h
  ios/ios_src/Search/Yelp/OAuthConsumer/OARequestParameter.m
  ios/ios_src/Search/Yelp/OAuthConsumer/OAServiceTicket.h
  ios/ios_src/Search/Yelp/OAuthConsumer/OAServiceTicket.m
  ios/ios_src/Search/Yelp/OAuthConsumer/OASignatureProviding.h
  ios/ios_src/Search/Yelp/OAuthConsumer/OAToken.h
  ios/ios_src/Search/Yelp/OAuthConsumer/OAToken.m
  ios/ios_src/Search/Yelp/OAuthConsumer/OATokenManager.h
  ios/ios_src/Search/Yelp/OAuthConsumer/OATokenManager.m
  ios/ios_src/Search/Yelp/OAuthConsumer/OAuthConsumer.h
)
set(sources ${sources} ${currsources})
set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-w")

source_group(\\_src\\Search\\Yelp\\OAuthConsumer FILES ${currsources})
include(ios/ios_src/Search/Yelp/OAuthConsumer/Categories/CMakeLists.txt)
include(ios/ios_src/Search/Yelp/OAuthConsumer/Crytpo/CMakeLists.txt)
endif(${IOS})
