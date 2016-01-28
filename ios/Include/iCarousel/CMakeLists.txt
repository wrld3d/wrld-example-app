set(headers ${headers} Include/iCarousel
)
set(currsources
  Include/iCarousel/CMakeLists.txt
  Include/iCarousel/iCarousel.h
  Include/iCarousel/iCarousel.m
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-fobjc-arc -w")

set(sources ${sources} ${currsources})
source_group(\\iCarousel FILES ${currsources})
