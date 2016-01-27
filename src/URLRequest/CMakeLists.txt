set(headers ${headers} src/URLRequest
)
set(currsources
  src/URLRequest/DeeplinkURLRequestedMessage.cpp
  src/URLRequest/DeeplinkURLRequestedMessage.h
  src/URLRequest/URLRequestedMessage.cpp
  src/URLRequest/URLRequestedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\URLRequest FILES ${currsources})
