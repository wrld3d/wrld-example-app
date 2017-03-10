if(${ANDROID})
set(headers ${headers} jni/SearchResultSection
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\jni\\SearchResultSection FILES ${currsources})
include(jni/SearchResultSection/View/CMakeLists.txt)
endif(${ANDROID})
