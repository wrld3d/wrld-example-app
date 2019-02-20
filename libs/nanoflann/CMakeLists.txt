set(headers ${headers} ../libs/nanoflann
)
set(currsources
  ../libs/nanoflann/nanoflann.hpp
)

set(sources ${sources} ${currsources})
source_group(\\src\\OfflineRouting\\SdkModel\\RoutingEngine\\nanoflann FILES ${currsources})
