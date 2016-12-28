set(headers ${headers} ../src/Search/Yelp/SdkModel
)
set(currsources
  ../src/Search/Yelp/SdkModel/CMakeLists.txt
 ../src/Search/Yelp/SdkModel/YelpCategoryModel.h
  ../src/Search/Yelp/SdkModel/ISearchTagToYelpCategoryMapper.h
  ../src/Search/Yelp/SdkModel/SearchTagToYelpCategoryMapper.h
  ../src/Search/Yelp/SdkModel/SearchTagToYelpCategoryMapper.cpp
  ../src/Search/Yelp/SdkModel/IYelpCategoryToTagMapper.h
  ../src/Search/Yelp/SdkModel/IYelpSearchQuery.h
  ../src/Search/Yelp/SdkModel/YelpBusinessQuery.cpp
  ../src/Search/Yelp/SdkModel/YelpBusinessQuery.h
  ../src/Search/Yelp/SdkModel/YelpBusinessQueryFactory.h
  ../src/Search/Yelp/SdkModel/YelpBusinessQueryFactory.cpp
  ../src/Search/Yelp/SdkModel/YelpBusinessJsonParser.cpp
  ../src/Search/Yelp/SdkModel/YelpBusinessJsonParser.h
  ../src/Search/Yelp/SdkModel/YelpSearchQuery.cpp
  ../src/Search/Yelp/SdkModel/YelpSearchQuery.h
  ../src/Search/Yelp/SdkModel/YelpSearchQueryFactory.h
  ../src/Search/Yelp/SdkModel/YelpSearchQueryFactory.cpp
  ../src/Search/Yelp/SdkModel/YelpCategoryToTagMapper.cpp
  ../src/Search/Yelp/SdkModel/YelpCategoryToTagMapper.h
  ../src/Search/Yelp/SdkModel/YelpSearchJsonParser.cpp
  ../src/Search/Yelp/SdkModel/YelpSearchJsonParser.h
  ../src/Search/Yelp/SdkModel/YelpSearchResultModel.cpp
  ../src/Search/Yelp/SdkModel/YelpSearchResultModel.h
  ../src/Search/Yelp/SdkModel/YelpSearchServiceModule.cpp
  ../src/Search/Yelp/SdkModel/YelpSearchServiceModule.h
  ../src/Search/Yelp/SdkModel/YelpSearchService.cpp
  ../src/Search/Yelp/SdkModel/YelpSearchService.h
  ../src/Search/Yelp/SdkModel/YelpParsingHelpers.cpp
  ../src/Search/Yelp/SdkModel/YelpParsingHelpers.h
  ../src/Search/Yelp/SdkModel/YelpCategoryMapperUpdater.cpp
  ../src/Search/Yelp/SdkModel/YelpCategoryMapperUpdater.h

)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Yelp\\SdkModel FILES ${currsources})
