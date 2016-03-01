if(${IOS})
set(headers ${headers} ios_src/Helpers/UIAnimation/Easing
)
set(currsources
  ios_src/Helpers/UIAnimation/Easing/BackCurve.h
  ios_src/Helpers/UIAnimation/Easing/CircleCurve.h
  ios_src/Helpers/UIAnimation/Easing/IEasingCurve.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Helpers\\UIAnimation\\Easing FILES ${currsources})
endif(${IOS})
