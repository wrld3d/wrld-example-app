set(headers ${headers} ../src/SearchResultSection/SdkModel
)
set(currsources
  ../src/SearchResultSection/SdkModel/CMakeLists.txt
  ../src/SearchResultSection/SdkModel/ISearchResultSectionModule.h
  ../src/SearchResultSection/SdkModel/SearchResultSectionItemSelectedMessageHandler.cpp
  ../src/SearchResultSection/SdkModel/SearchResultSectionItemSelectedMessageHandler.h
  ../src/SearchResultSection/SdkModel/SearchResultSectionModule.cpp
  ../src/SearchResultSection/SdkModel/SearchResultSectionModule.h
  ../src/SearchResultSection/SdkModel/SearchResultViewClearedObserver.cpp
  ../src/SearchResultSection/SdkModel/SearchResultViewClearedObserver.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchResultSection\\SdkModel FILES ${currsources})
