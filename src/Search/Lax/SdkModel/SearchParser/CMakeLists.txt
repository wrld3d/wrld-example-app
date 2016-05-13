set(headers ${headers} ../src/Search/Lax/SdkModel/SearchParser
)
set(currsources
  ../src/Search/Lax/SdkModel/SearchParser/LaxSearchParser.cpp
  ../src/Search/Lax/SdkModel/SearchParser/LaxSearchParser.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Lax\\SdkModel\\SearchParser FILES ${currsources})
