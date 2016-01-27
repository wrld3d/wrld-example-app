if(${IOS})
set(headers ${headers} ios/ios_src/ModalBackground
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\ModalBackground FILES ${currsources})
include(ios/ios_src/ModalBackground/View/CMakeLists.txt)
endif(${IOS})
