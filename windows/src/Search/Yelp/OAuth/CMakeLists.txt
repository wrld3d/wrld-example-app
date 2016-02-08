set(headers ${headers} src/Search/Yelp/OAuth
)
set(currsources
  src/Search/Yelp/OAuth/base64.cpp
  src/Search/Yelp/OAuth/base64.h
  src/Search/Yelp/OAuth/HMAC_SHA1.cpp
  src/Search/Yelp/OAuth/HMAC_SHA1.h
  src/Search/Yelp/OAuth/liboauthcpp.cpp
  src/Search/Yelp/OAuth/liboauthcpp.h
  src/Search/Yelp/OAuth/SHA1.cpp
  src/Search/Yelp/OAuth/SHA1.h
  src/Search/Yelp/OAuth/urlencode.cpp
  src/Search/Yelp/OAuth/urlencode.h
)

# This file in iOS needed some warning suppression. Might be the same here...
set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "/clr /EHa /Y- /w")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Search\\Yelp\\OAuth FILES ${currsources})
