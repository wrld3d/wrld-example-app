if(${ANDROID})
set(headers ${headers} jni/SearchMenu
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\jni\\SearchMenu FILES ${currsources})
include(jni/SearchMenu/View/CMakeLists.txt)
endif(${ANDROID})
