if(${ANDROID})
set(headers ${headers} jni/Watermark/View
)
set(currsources
  jni/Watermark/View/CMakeLists.txt
  jni/Watermark/View/IWatermarkViewModule.h
  jni/Watermark/View/WatermarkView.h
  jni/Watermark/View/WatermarkView.cpp
  jni/Watermark/View/WatermarkViewIncludes.h
  jni/Watermark/View/WatermarkJni.h
  jni/Watermark/View/WatermarkJni.cpp
  jni/Watermark/View/WatermarkViewModule.h
  jni/Watermark/View/WatermarkViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Watermark\\View FILES ${currsources})
endif(${ANDROID})
