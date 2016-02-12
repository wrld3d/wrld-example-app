if(${IOS})
set(headers ${headers} ios_src/Watermark
)
set(currsources
  ios_src/Watermark/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Watermark FILES ${currsources})
include(ios_src/Watermark/View/CMakeLists.txt)
endif(${IOS})
