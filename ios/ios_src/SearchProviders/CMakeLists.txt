if(${IOS})
set(headers ${headers} ios_src/SearchProviders
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchProviders FILES ${currsources})
include(ios_src/SearchProviders/View/CMakeLists.txt)
endif(${IOS})
