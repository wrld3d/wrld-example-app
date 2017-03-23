if(${ANDROID})
set(headers ${headers} jni/InteriorsPosition/View/SenionLab
)
set(currsources
  jni/InteriorsPosition/View/SenionLab/CMakeLists.txt
  jni/InteriorsPosition/View/SenionLab/SenionLabBroadcastReceiver.h
  jni/InteriorsPosition/View/SenionLab/SenionLabBroadcastReceiver.cpp
  jni/InteriorsPosition/View/SenionLab/SenionLabBroadcastReceiverJni.h
  jni/InteriorsPosition/View/SenionLab/SenionLabBroadcastReceiverJni.cpp
)
set(sources ${sources} ${currsources})
source_group(\\jni\\InteriorsPosition\\View\\SenionLab FILES ${currsources})
endif(${ANDROID})
