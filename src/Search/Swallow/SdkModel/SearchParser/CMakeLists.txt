set(headers ${headers} ../src/Search/Swallow/SdkModel/SearchParser
)
set(currsources
  ../src/Search/Swallow/SdkModel/SearchParser/SwallowSearchParser.cpp
  ../src/Search/Swallow/SdkModel/SearchParser/SwallowSearchParser.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Swallow\\SdkModel\\SearchParser FILES ${currsources})
