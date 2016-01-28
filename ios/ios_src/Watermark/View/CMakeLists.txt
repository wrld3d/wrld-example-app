if(${IOS})
set(headers ${headers} ios_src/Watermark/View
)
set(currsources
  ios_src/Watermark/View/CMakeLists.txt
  ios_src/Watermark/View/IWatermarkViewModule.h
  ios_src/Watermark/View/WatermarkView.h
  ios_src/Watermark/View/WatermarkView.mm
  ios_src/Watermark/View/WatermarkViewIncludes.h
  ios_src/Watermark/View/WatermarkViewInterop.h
  ios_src/Watermark/View/WatermarkViewInterop.mm
  ios_src/Watermark/View/WatermarkViewModule.h
  ios_src/Watermark/View/WatermarkViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Watermark\\View FILES ${currsources})
endif(${IOS})
