if(${IOS})
set(headers ${headers} ios_src/NavRouting/View/NavRoutingRerouteDialog
)
set(currsources
  ios_src/NavRouting/View/NavRoutingRerouteDialog/NavRoutingRerouteDialog.h
  ios_src/NavRouting/View/NavRoutingRerouteDialog/NavRoutingRerouteDialog.mm
  ios_src/NavRouting/View/NavRoutingRerouteDialog/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\NavRouting\\View\\NavRoutingRerouteDialog FILES ${currsources})
endif(${IOS})
