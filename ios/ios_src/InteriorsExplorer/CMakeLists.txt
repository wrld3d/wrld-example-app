if(${IOS})
set(headers ${headers} ios_src/InteriorsExplorer
)
set(currsources
  ios_src/InteriorsExplorer/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\InteriorsExplorer FILES ${currsources})
include(ios_src/InteriorsExplorer/View/CMakeLists.txt)
endif(${IOS})
