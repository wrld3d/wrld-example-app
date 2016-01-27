set(headers ${headers} src/Search/Combined/SdkModel
)
set(currsources
  src/Search/Combined/SdkModel/CombinedSearchService.cpp
  src/Search/Combined/SdkModel/CombinedSearchService.h
  src/Search/Combined/SdkModel/CombinedSearchServiceModule.cpp
  src/Search/Combined/SdkModel/CombinedSearchServiceModule.h
)
set(sources ${sources} ${currsources})
source_group(\\Search\\Combined\\SdkModel FILES ${currsources})
