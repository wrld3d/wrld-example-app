if(${ANDROID})
set(headers ${headers} jni/Menu/SdkModel
)
set(currsources
  jni/Menu/SdkModel/AndroidMenuReactionModel.h
  jni/Menu/SdkModel/AndroidMenuReactionModel.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Menu\\SdkModel FILES ${currsources})
endif(${ANDROID})
