if(${IOS})
set(headers ${headers} ios_src/Tours
)
set(currsources
  ios_src/Tours/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Tours FILES ${currsources})
include(ios_src/Tours/View/CMakeLists.txt)
endif(${IOS})
