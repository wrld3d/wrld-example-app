if(${IOS})
set(headers ${headers} ios/Include/iCarousel
)
set(currsources
  ios/Include/iCarousel/iCarousel.h
  ios/Include/iCarousel/iCarousel.m
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-fobjc-arc -w")

set(sources ${sources} ${currsources})
source_group(\\Include\\iCarousel FILES ${currsources})
endif(${IOS})
