if(${ANDROID})
set(headers ${headers} jni/Surveys
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Surveys FILES ${currsources})
include(jni/Surveys/View/CMakeLists.txt)
endif(${ANDROID})
