if(${ANDROID})
set(headers ${headers} jni/Helpers 
)
set(currsources
  jni/Helpers/AndroidImagePathHelpers.h
  jni/Helpers/ImagePathHelpers.cpp
  jni/Helpers/JniHelper.cpp
  jni/Helpers/JniHelper.h
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Helpers FILES ${currsources})
endif(${ANDROID})
