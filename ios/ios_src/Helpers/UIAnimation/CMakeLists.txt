if(${IOS})
set(headers ${headers} ios_src/Helpers/UIAnimation
)
set(currsources
  ios_src/Helpers/UIAnimation/ViewAlphaAnimator.h
  ios_src/Helpers/UIAnimation/ViewAlphaAnimator.mm
  ios_src/Helpers/UIAnimation/ViewAnimationController.h
  ios_src/Helpers/UIAnimation/ViewAnimationController.mm
  ios_src/Helpers/UIAnimation/ViewAnimatorBase.h
  ios_src/Helpers/UIAnimation/ViewAnimatorBase.mm
  ios_src/Helpers/UIAnimation/ViewFrameAnimator.h
  ios_src/Helpers/UIAnimation/ViewFrameAnimator.mm
  ios_src/Helpers/UIAnimation/ViewPositionAnimator.h
  ios_src/Helpers/UIAnimation/ViewPositionAnimator.mm
  ios_src/Helpers/UIAnimation/ViewSizeAnimator.h
  ios_src/Helpers/UIAnimation/ViewSizeAnimator.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\Helpers\\UIAnimation FILES ${currsources})
include(ios_src/Helpers/UIAnimation/Easing/CMakeLists.txt)
endif(${IOS})
