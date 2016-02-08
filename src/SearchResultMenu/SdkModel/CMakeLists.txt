set(headers ${headers} ../src/SearchResultMenu/SdkModel
)
set(currsources
  ../src/SearchResultMenu/SdkModel/CMakeLists.txt
  ../src/SearchResultMenu/SdkModel/ISearchResultMenuModule.h
  ../src/SearchResultMenu/SdkModel/SearchResultMenuItemSelectedMessageHandler.cpp
  ../src/SearchResultMenu/SdkModel/SearchResultMenuItemSelectedMessageHandler.h
  ../src/SearchResultMenu/SdkModel/SearchResultMenuModule.cpp
  ../src/SearchResultMenu/SdkModel/SearchResultMenuModule.h
  ../src/SearchResultMenu/SdkModel/SearchResultViewClearedObserver.cpp
  ../src/SearchResultMenu/SdkModel/SearchResultViewClearedObserver.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchResultMenu\\SdkModel FILES ${currsources})
