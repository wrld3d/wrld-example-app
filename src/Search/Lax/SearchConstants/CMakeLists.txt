set(headers ${headers} ../src/Search/Lax/SearchConstants
)
set(currsources
  ../src/Search/Lax/SearchConstants/LaxSearchConstants.cpp
  ../src/Search/Lax/SearchConstants/LaxSearchConstants.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\Lax\\SearchConstants FILES ${currsources})
