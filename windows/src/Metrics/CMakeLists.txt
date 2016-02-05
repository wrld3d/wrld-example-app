set(headers ${headers} src/Metrics
)
set(currsources
  src/Metrics/WindowsFlurryMetricsService.cpp
  src/Metrics/WindowsFlurryMetricsService.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "/clr /EHa /Y-")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Metrics FILES ${currsources})
