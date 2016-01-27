set(headers ${headers} src/Watermark/SdkModel
)
set(currsources
  src/Watermark/SdkModel/IWatermarkModule.h
  src/Watermark/SdkModel/WatermarkInteriorStateChangedObserver.cpp
  src/Watermark/SdkModel/WatermarkInteriorStateChangedObserver.h
  src/Watermark/SdkModel/WatermarkModel.h
  src/Watermark/SdkModel/WatermarkModule.cpp
  src/Watermark/SdkModel/WatermarkModule.h
)
set(sources ${sources} ${currsources})
source_group(\\Watermark\\SdkModel FILES ${currsources})
