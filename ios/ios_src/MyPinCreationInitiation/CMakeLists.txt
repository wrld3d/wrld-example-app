if(${IOS})
set(headers ${headers} ios_src/MyPinCreationInitiation
)
set(currsources
  ios_src/MyPinCreationInitiation/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\MyPinCreationInitiation FILES ${currsources})
include(ios_src/MyPinCreationInitiation/View/CMakeLists.txt)
endif(${IOS})
