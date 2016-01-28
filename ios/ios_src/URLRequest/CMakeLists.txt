if(${IOS})
set(headers ${headers} ios_src/URLRequest
)
set(currsources
  ios_src/URLRequest/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\URLRequest FILES ${currsources})
include(ios_src/URLRequest/View/CMakeLists.txt)
endif(${IOS})
