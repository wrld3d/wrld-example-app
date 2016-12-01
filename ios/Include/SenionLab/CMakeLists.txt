set(headers ${headers} Include/SenionLab
)
set(currsources
Include/SenionLab/CMakeLists.txt
Include/SenionLab/SLIndoorLocation.framework
)
set(sources ${sources} ${currsources})
source_group(\\SenionLab FILES ${currsources})
