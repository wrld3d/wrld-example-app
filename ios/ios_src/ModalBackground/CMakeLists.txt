if(${IOS})
set(headers ${headers} ios_src/ModalBackground
)
set(currsources
  ios_src/ModalBackground/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\ModalBackground FILES ${currsources})
include(ios_src/ModalBackground/View/CMakeLists.txt)
endif(${IOS})
