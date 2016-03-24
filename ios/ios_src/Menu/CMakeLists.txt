if(${IOS})
set(headers ${headers} ios_src/Menu
)
set(currsources
  ios_src/Menu/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Menu FILES ${currsources})
include(ios_src/Menu/View/CMakeLists.txt)
include(ios_src/Menu/SdkModel/CMakeLists.txt)
endif(${IOS})
