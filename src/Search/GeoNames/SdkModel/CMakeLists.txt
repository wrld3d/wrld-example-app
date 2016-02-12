set(headers ${headers} ../src/Search/GeoNames/SdkModel
)
set(currsources
  ../src/Search/GeoNames/SdkModel/CMakeLists.txt
  ../src/Search/GeoNames/SdkModel/GeoNamesJsonParser.cpp
  ../src/Search/GeoNames/SdkModel/GeoNamesJsonParser.h
  ../src/Search/GeoNames/SdkModel/GeoNamesSearchQuery.cpp
  ../src/Search/GeoNames/SdkModel/GeoNamesSearchQuery.h
  ../src/Search/GeoNames/SdkModel/GeoNamesSearchQueryFactory.cpp
  ../src/Search/GeoNames/SdkModel/GeoNamesSearchQueryFactory.h
  ../src/Search/GeoNames/SdkModel/GeoNamesSearchResultDto.cpp
  ../src/Search/GeoNames/SdkModel/GeoNamesSearchResultDto.h
  ../src/Search/GeoNames/SdkModel/GeoNamesSearchService.cpp
  ../src/Search/GeoNames/SdkModel/GeoNamesSearchService.h
  ../src/Search/GeoNames/SdkModel/GeoNamesSearchServiceModule.cpp
  ../src/Search/GeoNames/SdkModel/GeoNamesSearchServiceModule.h
  ../src/Search/GeoNames/SdkModel/IGeoNamesParser.h
  ../src/Search/GeoNames/SdkModel/IGeoNamesSearchQuery.h
  ../src/Search/GeoNames/SdkModel/IGeoNamesSearchQueryFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\GeoNames\\SdkModel FILES ${currsources})
