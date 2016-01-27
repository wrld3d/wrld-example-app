if(${IOS})
set(headers ${headers} ios/Include
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\Include FILES ${currsources})
include(ios/Include/Flurry/CMakeLists.txt)
include(ios/Include/FXImageView/CMakeLists.txt)
include(ios/Include/iCarousel/CMakeLists.txt)
endif(${IOS})
