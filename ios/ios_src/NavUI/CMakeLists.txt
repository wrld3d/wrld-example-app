if(${IOS})
set(headers ${headers} ios_src/NavUI
)
set(currsources
  ios_src/NavUI/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\NavUI FILES ${currsources})
include(ios_src/NavUI/View/CMakeLists.txt)
endif(${IOS})
