set(headers ${headers} ../src/Search/Combined/SdkModel
)
set(currsources
  ../src/Search/Combined/SdkModel/CMakeLists.txt
  ../src/Search/Combined/SdkModel/CombinedSearchService.cpp
  ../src/Search/Combined/SdkModel/CombinedSearchService.h
  ../src/Search/Combined/SdkModel/CombinedSearchServiceModule.cpp
  ../src/Search/Combined/SdkModel/CombinedSearchServiceModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Combined\\SdkModel FILES ${currsources})
