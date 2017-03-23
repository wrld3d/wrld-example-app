if(${ANDROID})
set(headers ${headers} jni/Metrics
)
set(currsources
  jni/Metrics/CMakeLists.txt
  jni/Metrics/AndroidFlurryMetricsService.h
  jni/Metrics/AndroidFlurryMetricsService.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Metrics FILES ${currsources})
endif(${ANDROID})
