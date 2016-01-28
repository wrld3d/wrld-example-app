set(headers ${headers} ../src/Search/SdkModel/MyPins
)
set(currsources
  ../src/Search/SdkModel/MyPins/CMakeLists.txt
  ../src/Search/SdkModel/MyPins/IMyPinsSearchResultRefreshService.h
  ../src/Search/SdkModel/MyPins/ISearchResultMyPinsService.h
  ../src/Search/SdkModel/MyPins/MyPinsSearchResultRefreshService.cpp
  ../src/Search/SdkModel/MyPins/MyPinsSearchResultRefreshService.h
  ../src/Search/SdkModel/MyPins/SearchResultMyPinsService.cpp
  ../src/Search/SdkModel/MyPins/SearchResultMyPinsService.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\SdkModel\\MyPins FILES ${currsources})
