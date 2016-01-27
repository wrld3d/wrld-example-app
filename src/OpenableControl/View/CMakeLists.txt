set(headers ${headers} src/OpenableControl/View
)
set(currsources
  src/OpenableControl/View/IOpenableControlViewModel.h
  src/OpenableControl/View/OpenableControlViewModelBase.cpp
  src/OpenableControl/View/OpenableControlViewModelBase.h
  src/OpenableControl/View/OpenableControlViewModelIncludes.h
)
set(sources ${sources} ${currsources})
source_group(\\OpenableControl\\View FILES ${currsources})
