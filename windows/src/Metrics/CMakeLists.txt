set(headers ${headers} src/Metrics
)
set(currsources
  src/Metrics/WindowsFlurryMetricsService.cpp
  src/Metrics/WindowsFlurryMetricsService.h
)

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Metrics FILES ${currsources})
