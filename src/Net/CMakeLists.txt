set(headers ${headers} ../src/Net
)
set(currsources
  ../src/Net/CMakeLists.txt
  ../src/Net/ConnectivityChangedViewMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Net FILES ${currsources})
include(../src/Net/SdkModel/CMakeLists.txt)
