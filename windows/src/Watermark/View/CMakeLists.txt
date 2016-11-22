set(headers ${headers} src/Watermark/View
)
set(currsources_noclr
  src/Watermark/View/WatermarkViewIncludes.h
  src/Watermark/View/WatermarkViewModule.cpp
  src/Watermark/View/WatermarkViewModule.h
  src/Watermark/View/WatermarkView.h
)

set(currsources
  src/Watermark/View/WatermarkCLI.cpp
  src/Watermark/View/WatermarkCLI.h
  src/Watermark/View/WatermarkView.cpp
  src/Watermark/View/WatermarkViewImpl.h
  src/Watermark/View/WatermarkViewImpl.cpp
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
set_source_files_properties(${currsources_noclr} PROPERTIES COMPILE_FLAGS "${no_clr_compile_flags}")

set(sources ${sources} ${currsources} ${currsources_noclr})
source_group(\\windows_src\\\\Watermark\\View FILES ${currsources} ${currsources_noclr})
