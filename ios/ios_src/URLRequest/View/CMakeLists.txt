if(${IOS})
set(headers ${headers} ios_src/URLRequest/View
)
set(currsources
  ios_src/URLRequest/View/CMakeLists.txt
  ios_src/URLRequest/View/URLRequestHandler.h
  ios_src/URLRequest/View/URLRequestHandler.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\URLRequest\\View FILES ${currsources})
endif(${IOS})
