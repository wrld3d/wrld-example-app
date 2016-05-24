set(headers ${headers} ../libs/OAuth
)
set(currsources
  ../libs/OAuth/base64.cpp
  ../libs/OAuth/base64.h
  ../libs/OAuth/HMAC_SHA1.cpp
  ../libs/OAuth/HMAC_SHA1.h
  ../libs/OAuth/liboauthcpp.cpp
  ../libs/OAuth/liboauthcpp.h
  ../libs/OAuth/SHA1.cpp
  ../libs/OAuth/SHA1.h
  ../libs/OAuth/urlencode.cpp
  ../libs/OAuth/urlencode.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Yelp\\SdkModel\\OAuth FILES ${currsources})
