if(${IOS})
set(headers ${headers} ios_src/MyPinDetails
)
set(currsources
  ios_src/MyPinDetails/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\MyPinDetails FILES ${currsources})
include(ios_src/MyPinDetails/View/CMakeLists.txt)
endif(${IOS})
