if(${IOS})
set(headers ${headers} ios_src/FlattenButton
)
set(currsources
  ios_src/FlattenButton/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\FlattenButton FILES ${currsources})
include(ios_src/FlattenButton/View/CMakeLists.txt)
endif(${IOS})
