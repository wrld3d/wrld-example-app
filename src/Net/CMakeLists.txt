set(headers ${headers} src/Net
)
set(currsources
  src/Net/ConnectivityChangedViewMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\Net FILES ${currsources})
include(src/Net/SdkModel/CMakeLists.txt)
