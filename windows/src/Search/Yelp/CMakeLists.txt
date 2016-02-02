set(headers ${headers} src/Search/Yelp
)
set(currsources
  src/Search/Yelp/WindowsYelpBusinessQuery.cpp
  src/Search/Yelp/WindowsYelpBusinessQuery.h
  src/Search/Yelp/WindowsYelpSearchQuery.cpp
  src/Search/Yelp/WindowsYelpSearchQuery.h
  src/Search/Yelp/WindowsYelpSearchQueryCLI.cpp
  src/Search/Yelp/WindowsYelpSearchQueryCLI.h
  src/Search/Yelp/WindowsYelpSearchQueryFactory.cpp
  src/Search/Yelp/WindowsYelpSearchQueryFactory.h
  src/Search/Yelp/WindowsYelpSearchServiceModule.cpp
  src/Search/Yelp/WindowsYelpSearchServiceModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "/clr /EHa")

set(sources ${sources} ${currsources})
source_group(\\Search\\Yelp FILES ${currsources})
include(src/Search/Yelp/OAuth/CMakeLists.txt)
