if(${IOS})
set(headers ${headers} ios_src/Metrics
)
set(currsources
  ios_src/Metrics/CMakeLists.txt
  ios_src/Metrics/iOSFlurryMetricsService.h
  ios_src/Metrics/iOSFlurryMetricsService.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Metrics FILES ${currsources})
endif(${IOS})
