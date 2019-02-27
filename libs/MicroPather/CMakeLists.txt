set(headers ${headers} ../libs/MicroPather
)
set(currsources
  ../libs/MicroPather/micropather.cpp
  ../libs/MicroPather/micropather.h
)

set(sources ${sources} ${currsources})
source_group(\\src\\OfflineRouting\\SdkModel\\RoutingEngine\\MicroPather FILES ${currsources})
