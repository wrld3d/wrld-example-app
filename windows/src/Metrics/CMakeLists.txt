set(headers ${headers} src/Metrics
)
set(currsources
  src/Metrics/DummyMetricsService.cpp
  src/Metrics/DummyMetricsService.h
)

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Metrics FILES ${currsources})
