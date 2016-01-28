set(headers ${headers} ../src/Metrics
)
set(currsources
  ../src/Metrics/CMakeLists.txt
  ../src/Metrics/IMetricsService.h
  ../src/Metrics/Metrics.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Metrics FILES ${currsources})
