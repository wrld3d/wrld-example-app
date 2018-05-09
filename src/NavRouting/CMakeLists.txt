set(headers ${headers} ../src/NavRouting
)
set(currsources
  ../src/NavRouting/CMakeLists.txt
  ../src/NavRouting/NavRouting.h
  ../src/NavRouting/NavRoutingQueryCompletedMessage.cpp
  ../src/NavRouting/NavRoutingQueryCompletedMessage.h
  ../src/NavRouting/NavRoutingSelectEndLocationClickedMessage.h
  ../src/NavRouting/NavRoutingSelectStartLocationClickedMessage.h
  ../src/NavRouting/NavRoutingViewClosedMessage.h
  ../src/NavRouting/NavRoutingViewStartEndLocationSwappedMessage.h
  ../src/NavRouting/NavRoutingViewPerformedRouteQueryMessage.cpp
  ../src/NavRouting/NavRoutingViewPerformedRouteQueryMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\NavRouting FILES ${currsources})
include(../src/NavRouting/SdkModel/CMakeLists.txt)
include(../src/NavRouting/View/CMakeLists.txt)
