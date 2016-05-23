set(headers ${headers} ../src/Search/Yelp/SdkModel/OAuth
)
set(currsources
  ../src/Search/Yelp/SdkModel/OAuth/base64.cpp
  ../src/Search/Yelp/SdkModel/OAuth/base64.h
  ../src/Search/Yelp/SdkModel/OAuth/HMAC_SHA1.cpp
  ../src/Search/Yelp/SdkModel/OAuth/HMAC_SHA1.h
  ../src/Search/Yelp/SdkModel/OAuth/liboauthcpp.cpp
  ../src/Search/Yelp/SdkModel/OAuth/liboauthcpp.h
  ../src/Search/Yelp/SdkModel/OAuth/SHA1.cpp
  ../src/Search/Yelp/SdkModel/OAuth/SHA1.h
  ../src/Search/Yelp/SdkModel/OAuth/urlencode.cpp
  ../src/Search/Yelp/SdkModel/OAuth/urlencode.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Yelp\\SdkModel\\OAuth FILES ${currsources})
