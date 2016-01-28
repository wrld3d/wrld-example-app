if(${IOS})
set(headers ${headers} ios_src/ImageStore
)
set(currsources
  ios_src/ImageStore/CMakeLists.txt
  ios_src/ImageStore/ImageFetchOperation.h
  ios_src/ImageStore/ImageFetchOperation.mm
  ios_src/ImageStore/ImageStore.h
  ios_src/ImageStore/ImageStore.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\ImageStore FILES ${currsources})
endif(${IOS})
