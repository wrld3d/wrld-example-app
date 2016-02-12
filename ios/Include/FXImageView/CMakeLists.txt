set(headers ${headers} Include/FXImageView
)
set(currsources
  Include/FXImageView/CMakeLists.txt
  Include/FXImageView/FXImageView.h
  Include/FXImageView/FXImageView.m
  Include/FXImageView/UIImage+FX.h
  Include/FXImageView/UIImage+FX.m
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "-fobjc-arc -w")

set(sources ${sources} ${currsources})
source_group(\\FXImageView FILES ${currsources})
