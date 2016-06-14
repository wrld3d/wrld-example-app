set(headers ${headers} ../src/Search/EegeoPois/SdkModel
)
set(currsources
  ../src/Search/EegeoPois/SdkModel/CMakeLists.txt
  ../src/Search/EegeoPois/SdkModel/EegeoJsonParser.cpp
  ../src/Search/EegeoPois/SdkModel/EegeoJsonParser.h
  ../src/Search/EegeoPois/SdkModel/EegeoSearchQuery.cpp
  ../src/Search/EegeoPois/SdkModel/EegeoSearchQuery.h
  ../src/Search/EegeoPois/SdkModel/EegeoInteriorSearchQuery.h
  ../src/Search/EegeoPois/SdkModel/EegeoInteriorSearchQuery.cpp
  ../src/Search/EegeoPois/SdkModel/EegeoReadableTagMapper.h
  ../src/Search/EegeoPois/SdkModel/EegeoReadableTagMapper.cpp
  ../src/Search/EegeoPois/SdkModel/EegeoSearchQueryFactory.cpp
  ../src/Search/EegeoPois/SdkModel/EegeoSearchQueryFactory.h
  ../src/Search/EegeoPois/SdkModel/EegeoSearchService.cpp
  ../src/Search/EegeoPois/SdkModel/EegeoSearchService.h
  ../src/Search/EegeoPois/SdkModel/EegeoSearchServiceModule.cpp
  ../src/Search/EegeoPois/SdkModel/EegeoSearchServiceModule.h
  ../src/Search/EegeoPois/SdkModel/EegeoSearchResultModel.h
  ../src/Search/EegeoPois/SdkModel/EegeoSearchResultModel.cpp
  ../src/Search/EegeoPois/SdkModel/IEegeoParser.h
  ../src/Search/EegeoPois/SdkModel/IEegeoSearchQuery.h
  ../src/Search/EegeoPois/SdkModel/IEegeoSearchQueryFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\EegeoPois\\SdkModel FILES ${currsources})
