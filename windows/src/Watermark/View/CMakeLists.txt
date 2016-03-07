set(headers ${headers} src/Watermark/View
)
set(currsources
  src/Watermark/View/IWatermarkViewModule.h
  src/Watermark/View/WatermarkCLI.cpp
  src/Watermark/View/WatermarkCLI.h
  src/Watermark/View/WatermarkView.cpp
  src/Watermark/View/WatermarkView.h
  src/Watermark/View/WatermarkViewIncludes.h
  src/Watermark/View/WatermarkViewModule.cpp
  src/Watermark/View/WatermarkViewModule.h
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")

set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Watermark\\View FILES ${currsources})
