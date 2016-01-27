set(headers ${headers} src/Watermark
)
set(currsources
  src/Watermark/SetWatermarkVisibilityMessage.h
  src/Watermark/Watermark.h
  src/Watermark/WatermarkAlignmentStateChangedMessage.h
  src/Watermark/WatermarkModelChangedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\Watermark FILES ${currsources})
include(src/Watermark/SdkModel/CMakeLists.txt)
include(src/Watermark/View/CMakeLists.txt)
