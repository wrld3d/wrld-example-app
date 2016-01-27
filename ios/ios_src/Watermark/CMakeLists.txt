if(${IOS})
set(headers ${headers} ios/ios_src/Watermark
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Watermark FILES ${currsources})
include(ios/ios_src/Watermark/View/CMakeLists.txt)
endif(${IOS})
