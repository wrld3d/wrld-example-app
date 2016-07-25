if(${IOS})
set(headers ${headers} ios_src/SenionLab/FrameWork
)
set(currsources
  ios_src/SenionLab/FrameWork/CMakeLists.txt
  ios_src/SenionLab/FrameWork/SLIndoorLocation.framework
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\SenionLab\\FrameWork FILES ${currsources})
endif(${IOS})
