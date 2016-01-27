if(${IOS})
set(headers ${headers} ios/ios_src/SecondaryMenu
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\SecondaryMenu FILES ${currsources})
include(ios/ios_src/SecondaryMenu/View/CMakeLists.txt)
endif(${IOS})
