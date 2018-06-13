if(${IOS})
set(headers ${headers} ios_src/NavRouting
)
set(currsources
ios_src/NavRouting/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\NavRouting FILES ${currsources})
include(ios_src/NavRouting/View/CMakeLists.txt)
endif(${IOS})
