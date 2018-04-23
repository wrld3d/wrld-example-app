if(${IOS})
set(headers ${headers} ios_src/SearchProviders/View
)
set(currsources
  ios_src/SearchProviders/View/SearchProvider.mm
  ios_src/SearchProviders/View/SearchProvider.h
  ios_src/SearchProviders/View/WidgetQueryContext.mm
  ios_src/SearchProviders/View/WidgetQueryContext.h
  ios_src/SearchProviders/View/WidgetSearchProvider.mm
  ios_src/SearchProviders/View/WidgetSearchProvider.h
  ios_src/SearchProviders/View/WidgetSearchResultModel.mm
  ios_src/SearchProviders/View/WidgetSearchResultModel.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SearchProviders\\View FILES ${currsources})
endif(${IOS})
