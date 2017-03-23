set(headers ${headers} jni/MyPins
)
set(currsources
)
set(sources ${sources} ${currsources})
source_group(\\jni\\\\MyPins FILES ${currsources})
include(jni/MyPins/View/CMakeLists.txt)
