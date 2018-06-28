if(${IOS})
set(headers ${headers} ios_src/NavRouting/View/NavRoutingCalculatingRoute
)
set(currsources
  ios_src/NavRouting/View/NavRoutingCalculatingRoute/NavRoutingCalculatingRoute.h
  ios_src/NavRouting/View/NavRoutingCalculatingRoute/NavRoutingCalculatingRoute.mm
  ios_src/NavRouting/View/NavRoutingCalculatingRoute/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\NavRouting\\View\\NavRoutingCalculatingRoute FILES ${currsources})
endif(${IOS})
