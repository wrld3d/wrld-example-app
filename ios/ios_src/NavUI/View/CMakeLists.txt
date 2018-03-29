if(${IOS})
set(headers ${headers} ios_src/NavUI/View
)
set(currsources
  ios_src/NavUI/View/NavUIViewIncludes.h
  ios_src/NavUI/View/NavUIViewModule.h
  ios_src/NavUI/View/NavUIViewModule.mm
  ios_src/NavUI/View/NavUIViewRouteUpdateHandler.h
  ios_src/NavUI/View/NavUIViewRouteUpdateHandler.mm
  ios_src/NavUI/View/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\NavUI\\View FILES ${currsources})
endif(${IOS})
