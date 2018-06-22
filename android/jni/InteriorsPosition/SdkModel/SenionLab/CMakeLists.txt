if(${ANDROID})
set(headers ${headers} jni/InteriorsPosition/SdkModel/SenionLab
)
set(currsources
  jni/InteriorsPosition/SdkModel/SenionLab/CMakeLists.txt
  jni/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationInterop.h
  jni/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationInterop.cpp
  jni/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationInteropJni.h
  jni/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationInteropJni.cpp
  jni/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationModule.h
  jni/InteriorsPosition/SdkModel/SenionLab/SenionLabLocationModule.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InteriorsPosition\\SdkModel\\SenionLab FILES ${currsources})
endif(${ANDROID})
