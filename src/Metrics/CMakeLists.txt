set(headers ${headers} src/Metrics
)
set(currsources
  src/Metrics/IMetricsService.h
  src/Metrics/Metrics.h
)
set(sources ${sources} ${currsources})
source_group(\\Metrics FILES ${currsources})
