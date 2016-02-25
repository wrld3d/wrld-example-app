if(${IOS})
set(headers ${headers} ios_src/SearchMenu
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchMenu FILES ${currsources})
include(ios_src/SearchMenu/View/CMakeLists.txt)
endif(${IOS})
