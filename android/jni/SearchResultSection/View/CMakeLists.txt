if(${ANDROID})
set(headers ${headers} jni/SearchResultSection/View
)
set(currsources
  jni/SearchResultSection/View/ISearchResultSectionViewModule.h
  jni/SearchResultSection/View/SearchResultSectionViewIncludes.h
  jni/SearchResultSection/View/SearchResultSectionViewModule.h
  jni/SearchResultSection/View/SearchResultSectionViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\SearchResultSection\\View FILES ${currsources})
endif(${ANDROID})
