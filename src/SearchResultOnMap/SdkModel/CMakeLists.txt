set(headers ${headers} ../src/SearchResultOnMap/SdkModel
)
set(currsources
  ../src/SearchResultOnMap/SdkModel/CMakeLists.txt
  ../src/SearchResultOnMap/SdkModel/ISearchResultOnMapModel.h
  ../src/SearchResultOnMap/SdkModel/ISearchResultOnMapModule.h
  ../src/SearchResultOnMap/SdkModel/SearchResultOnMapModel.cpp
  ../src/SearchResultOnMap/SdkModel/SearchResultOnMapModel.h
  ../src/SearchResultOnMap/SdkModel/SearchResultOnMapModule.cpp
  ../src/SearchResultOnMap/SdkModel/SearchResultOnMapModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\SearchResultOnMap\\SdkModel FILES ${currsources})
