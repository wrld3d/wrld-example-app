if(${ANDROID})
set(headers ${headers} jni/Watermark
)
set(currsources
  jni/Watermark/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Watermark FILES ${currsources})
include(jni/Watermark/View/CMakeLists.txt)
endif(${ANDROID})
