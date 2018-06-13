set(headers ${headers} ../src/Search
)
set(currsources
  ../src/Search/AutocompleteSuggestionsReceivedMessage.cpp
  ../src/Search/AutocompleteSuggestionsReceivedMessage.h
  ../src/Search/CMakeLists.txt
  ../src/Search/Search.h
  ../src/Search/SearchQueryPerformedMessage.cpp
  ../src/Search/SearchQueryPerformedMessage.h
  ../src/Search/SearchQueryRefreshedMessage.cpp
  ../src/Search/SearchQueryRefreshedMessage.h
  ../src/Search/SearchQueryRemovedMessage.cpp
  ../src/Search/SearchQueryRemovedMessage.h
  ../src/Search/SearchQueryResponseReceivedMessage.cpp
  ../src/Search/SearchQueryResponseReceivedMessage.h
  ../src/Search/SearchVendorNames.cpp
  ../src/Search/SearchVendorNames.h
  ../src/Search/SearchQueryResultsRemovedMessage.cpp
  ../src/Search/SearchQueryResultsRemovedMessage.h
  ../src/Search/SearchQueryRequestMessage.cpp
  ../src/Search/SearchQueryRequestMessage.h
  ../src/Search/SearchQueryClearRequestMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search FILES ${currsources})
include(../src/Search/SelectFirstResult/CMakeLists.txt)
include(../src/Search/Combined/CMakeLists.txt)
include(../src/Search/EegeoPois/CMakeLists.txt)
include(../src/Search/GeoNames/CMakeLists.txt)
include(../src/Search/SdkModel/CMakeLists.txt)
include(../src/Search/Yelp/CMakeLists.txt)
