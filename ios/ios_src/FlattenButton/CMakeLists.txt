if(${IOS})
set(headers ${headers} ios/ios_src/FlattenButton
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\FlattenButton FILES ${currsources})
include(ios/ios_src/FlattenButton/View/CMakeLists.txt)
endif(${IOS})
