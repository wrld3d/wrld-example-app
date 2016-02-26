if(${IOS})
set(headers ${headers} ios_src/LinkOutObserver
)
set(currsources
  ios_src/LinkOutObserver/LinkOutObserver.h
  ios_src/LinkOutObserver/LinkOutObserver.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\LinkOutObserver FILES ${currsources})
endif(${IOS})
