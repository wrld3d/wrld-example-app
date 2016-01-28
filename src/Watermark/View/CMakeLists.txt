set(headers ${headers} ../src/Watermark/View
)
set(currsources
  ../src/Watermark/View/CMakeLists.txt
  ../src/Watermark/View/IWatermarkDataFactory.h
  ../src/Watermark/View/IWatermarkDataRepository.h
  ../src/Watermark/View/IWatermarkView.h
  ../src/Watermark/View/IWatermarkViewModel.h
  ../src/Watermark/View/WatermarkController.cpp
  ../src/Watermark/View/WatermarkController.h
  ../src/Watermark/View/WatermarkData.h
  ../src/Watermark/View/WatermarkDataFactory.cpp
  ../src/Watermark/View/WatermarkDataFactory.h
  ../src/Watermark/View/WatermarkDataRepository.cpp
  ../src/Watermark/View/WatermarkDataRepository.h
  ../src/Watermark/View/WatermarkScreenControl.cpp
  ../src/Watermark/View/WatermarkScreenControl.h
  ../src/Watermark/View/WatermarkViewModel.cpp
  ../src/Watermark/View/WatermarkViewModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Watermark\\View FILES ${currsources})
