if(${IOS})
set(headers ${headers} ios/ios_src/URLRequest/View
)
set(currsources
  ios/ios_src/URLRequest/View/URLRequestHandler.h
  ios/ios_src/URLRequest/View/URLRequestHandler.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\URLRequest\\View FILES ${currsources})
endif(${IOS})
