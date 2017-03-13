if(${IOS})
set(headers ${headers} ios_src/InteriorsPosition
)
set(currsources
  ios_src/InteriorsPosition/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\InteriorsPosition FILES ${currsources})
include(ios_src/InteriorsPosition/SdkModel/CMakeLists.txt)
endif(${IOS})
