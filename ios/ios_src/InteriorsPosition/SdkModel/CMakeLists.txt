if(${IOS})
set(headers ${headers} ios_src/InteriorsPosition/SdkModel
)
set(currsources
  ios_src/InteriorsPosition/SdkModel/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\InteriorsPosition\\SdkModel FILES ${currsources})
include(ios_src/InteriorsPosition/SdkModel/IndoorAtlas/CMakeLists.txt)
endif(${IOS})
