set(headers ${headers} src/Watermark
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Watermark FILES ${currsources})
include(src/Watermark/View/CMakeLists.txt)
