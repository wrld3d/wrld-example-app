if(${IOS})
set(headers ${headers} ios_src/SearchProviders/View
)
set(currsources
  ios_src/SearchProviders/View/DummySearchProvider.mm
  ios_src/SearchProviders/View/DummySearchProvider.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchMenu\\View FILES ${currsources})
endif(${IOS})
