if(${IOS})
set(headers ${headers} ios_src/Options
)
set(currsources
  ios_src/Options/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Options FILES ${currsources})
include(ios_src/Options/SdkModel/CMakeLists.txt)
include(ios_src/Options/View/CMakeLists.txt)
endif(${IOS})
