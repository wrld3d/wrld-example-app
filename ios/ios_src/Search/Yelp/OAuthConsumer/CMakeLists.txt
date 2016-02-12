if(${IOS})
set(headers ${headers} ios_src/Search/Yelp/OAuthConsumer
)
set(currsources
  ios_src/Search/Yelp/OAuthConsumer/CMakeLists.txt
  ios_src/Search/Yelp/OAuthConsumer/OACall.h
  ios_src/Search/Yelp/OAuthConsumer/OACall.m
  ios_src/Search/Yelp/OAuthConsumer/OAConsumer.h
  ios_src/Search/Yelp/OAuthConsumer/OAConsumer.m
  ios_src/Search/Yelp/OAuthConsumer/OADataFetcher.h
  ios_src/Search/Yelp/OAuthConsumer/OADataFetcher.m
  ios_src/Search/Yelp/OAuthConsumer/OAHMAC_SHA1SignatureProvider.h
  ios_src/Search/Yelp/OAuthConsumer/OAHMAC_SHA1SignatureProvider.m
  ios_src/Search/Yelp/OAuthConsumer/OAMutableURLRequest.h
  ios_src/Search/Yelp/OAuthConsumer/OAMutableURLRequest.m
  ios_src/Search/Yelp/OAuthConsumer/OAPlaintextSignatureProvider.h
  ios_src/Search/Yelp/OAuthConsumer/OAPlaintextSignatureProvider.m
  ios_src/Search/Yelp/OAuthConsumer/OAProblem.h
  ios_src/Search/Yelp/OAuthConsumer/OAProblem.m
  ios_src/Search/Yelp/OAuthConsumer/OARequestParameter.h
  ios_src/Search/Yelp/OAuthConsumer/OARequestParameter.m
  ios_src/Search/Yelp/OAuthConsumer/OAServiceTicket.h
  ios_src/Search/Yelp/OAuthConsumer/OAServiceTicket.m
  ios_src/Search/Yelp/OAuthConsumer/OASignatureProviding.h
  ios_src/Search/Yelp/OAuthConsumer/OAToken.h
  ios_src/Search/Yelp/OAuthConsumer/OAToken.m
  ios_src/Search/Yelp/OAuthConsumer/OATokenManager.h
  ios_src/Search/Yelp/OAuthConsumer/OATokenManager.m
  ios_src/Search/Yelp/OAuthConsumer/OAuthConsumer.h
)
set(sources ${sources} ${currsources})

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-w")

source_group(\\ios_src\\Search\\Yelp\\OAuthConsumer FILES ${currsources})
include(ios_src/Search/Yelp/OAuthConsumer/Categories/CMakeLists.txt)
include(ios_src/Search/Yelp/OAuthConsumer/Crytpo/CMakeLists.txt)
endif(${IOS})
