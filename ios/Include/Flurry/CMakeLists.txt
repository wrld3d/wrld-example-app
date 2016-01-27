if(${IOS})
set(headers ${headers} ios/Include/Flurry
)
set(currsources
  ios/Include/Flurry/Flurry.h
)
set(sources ${sources} ${currsources})
source_group(\\Include\\Flurry FILES ${currsources})
endif(${IOS})
