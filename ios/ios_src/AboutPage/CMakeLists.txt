if(${IOS})
set(headers ${headers} ios_src/AboutPage
)
set(currsources
  ios_src/AboutPage/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\AboutPage FILES ${currsources})
include(ios_src/AboutPage/View/CMakeLists.txt)
endif(${IOS})
