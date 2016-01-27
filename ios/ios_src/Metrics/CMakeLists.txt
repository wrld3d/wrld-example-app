if(${IOS})
set(headers ${headers} ios/ios_src/Metrics
)
set(currsources
  ios/ios_src/Metrics/iOSFlurryMetricsService.h
  ios/ios_src/Metrics/iOSFlurryMetricsService.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\Metrics FILES ${currsources})
endif(${IOS})
