if(${IOS})
set(headers ${headers} ios_src/ApplicationConfig
)
set(currsources
  ios_src/ApplicationConfig/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\ApplicationConfig FILES ${currsources})
include(ios_src/ApplicationConfig/SdkModel/CMakeLists.txt)
endif(${IOS})
