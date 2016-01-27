if(${IOS})
set(headers ${headers} ios/ios_src/ImageStore
)
set(currsources
  ios/ios_src/ImageStore/ImageFetchOperation.h
  ios/ios_src/ImageStore/ImageFetchOperation.mm
  ios/ios_src/ImageStore/ImageStore.h
  ios/ios_src/ImageStore/ImageStore.mm
)
set(sources ${sources} ${currsources})
source_group(\\_src\\ImageStore FILES ${currsources})
endif(${IOS})
