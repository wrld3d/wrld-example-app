if(${IOS})
set(headers ${headers} ios_src/Compass
)
set(currsources
  ios_src/Compass/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Compass FILES ${currsources})
include(ios_src/Compass/View/CMakeLists.txt)
endif(${IOS})
