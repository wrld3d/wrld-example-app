set(headers ${headers} ../src/Search/Swallow/SearchConstants
)
set(currsources
  ../src/Search/Swallow/SearchConstants/SwallowSearchConstants.cpp
  ../src/Search/Swallow/SearchConstants/SwallowSearchConstants.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Swallow\\SearchConstants FILES ${currsources})
