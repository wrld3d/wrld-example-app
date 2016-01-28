set(headers ${headers} ../src/Modality
)
set(currsources
  ../src/Modality/CMakeLists.txt
  ../src/Modality/Modality.h
  ../src/Modality/ModalityChangedMessage.cpp
  ../src/Modality/ModalityChangedMessage.h
  ../src/Modality/UpdateNativeModalBackgroundMessage.cpp
  ../src/Modality/UpdateNativeModalBackgroundMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Modality FILES ${currsources})
include(../src/Modality/View/CMakeLists.txt)
