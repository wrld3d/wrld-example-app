if(${IOS})
set(headers ${headers} ios_src/DirectionsMenuInitiation
)
set(currsources
  ios_src/DirectionsMenuInitiation/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\DirectionsMenuInitiation FILES ${currsources})
include(ios_src/DirectionsMenuInitiation/View/CMakeLists.txt)
endif(${IOS})
