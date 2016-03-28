set(headers ${headers} src/Menu/SdkModel
)
set(currsources
  src/Menu/SdkModel/WindowsMenuReactionModel.h
  src/Menu/SdkModel/WindowsMenuReactionModel.cpp
)

set_source_files_properties(${currsources} PROPERTIES COMPILE_FLAGS "${clr_compile_flags}")
 
set(sources ${sources} ${currsources})
source_group(\\windows_src\\\\Menu\\SdkModel FILES ${currsources})
