if(${IOS})
set(headers ${headers} ios/ios_src/Watermark/View
)
set(currsources
  ios/ios_src/Watermark/View/IWatermarkViewModule.h
  ios/ios_src/Watermark/View/WatermarkView.h
  ios/ios_src/Watermark/View/WatermarkView.mm
  ios/ios_src/Watermark/View/WatermarkViewIncludes.h
  ios/ios_src/Watermark/View/WatermarkViewInterop.h
  ios/ios_src/Watermark/View/WatermarkViewInterop.mm
  ios/ios_src/Watermark/View/WatermarkViewModule.h
  ios/ios_src/Watermark/View/WatermarkViewModule.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Watermark\\View FILES ${currsources})
endif(${IOS})
