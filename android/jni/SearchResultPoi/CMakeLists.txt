if(${ANDROID})
set(headers ${headers} jni/SearchResultPoi
)
set(currsources
  jni/SearchResultPoi/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\SearchResultPoi FILES ${currsources})
include(jni/SearchResultPoi/View/CMakeLists.txt)
endif(${ANDROID})
