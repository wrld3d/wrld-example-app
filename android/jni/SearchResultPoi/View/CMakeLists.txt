if(${ANDROID})
set(headers ${headers} jni/SearchResultPoi/View
)
set(currsources
  jni/SearchResultPoi/View/CMakeLists.txt
  jni/SearchResultPoi/View/ISearchResultPoiViewModule.h
  jni/SearchResultPoi/View/SearchResultPoiJni.h
  jni/SearchResultPoi/View/SearchResultPoiJni.cpp
  jni/SearchResultPoi/View/SearchResultPoiView.h
  jni/SearchResultPoi/View/SearchResultPoiView.cpp
  jni/SearchResultPoi/View/SearchResultPoiViewIncludes.h
  jni/SearchResultPoi/View/SearchResultPoiViewModule.h
  jni/SearchResultPoi/View/SearchResultPoiViewModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\SearchResultPoi\\View FILES ${currsources})
endif(${ANDROID})
