if(${IOS})
set(headers ${headers} ios/Include/FXImageView
)
set(currsources
  ios/Include/FXImageView/FXImageView.h
  ios/Include/FXImageView/FXImageView.m
  ios/Include/FXImageView/UIImage+FX.h
  ios/Include/FXImageView/UIImage+FX.m
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-fobjc-arc -w")

set(sources ${sources} ${currsources})
source_group(\\Include\\FXImageView FILES ${currsources})
endif(${IOS})
