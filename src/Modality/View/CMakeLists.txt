set(headers ${headers} ../src/Modality/View
)
set(currsources
  ../src/Modality/View/CMakeLists.txt
  ../src/Modality/View/IModalBackgroundView.h
  ../src/Modality/View/IModalityController.h
  ../src/Modality/View/IModalityModel.h
  ../src/Modality/View/IModalityModule.h
  ../src/Modality/View/ModalBackgroundController.cpp
  ../src/Modality/View/ModalBackgroundController.h
  ../src/Modality/View/ModalityController.cpp
  ../src/Modality/View/ModalityController.h
  ../src/Modality/View/ModalityModel.cpp
  ../src/Modality/View/ModalityModel.h
  ../src/Modality/View/ModalityModule.cpp
  ../src/Modality/View/ModalityModule.h
  ../src/Modality/View/ModalityObserver.cpp
  ../src/Modality/View/ModalityObserver.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Modality\\View FILES ${currsources})
