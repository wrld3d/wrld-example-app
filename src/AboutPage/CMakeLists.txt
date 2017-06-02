set(headers ${headers} ../src/AboutPage
)
set(currsources
  ../src/AboutPage/AboutPageIndoorPositionTypeMessage.cpp
  ../src/AboutPage/AboutPageIndoorPositionTypeMessage.h
  ../src/AboutPage/AboutPageSenionDataMessage.cpp
  ../src/AboutPage/AboutPageSenionDataMessage.h
  ../src/AboutPage/AboutPageIndoorAtlasDataMessage.cpp
  ../src/AboutPage/AboutPageIndoorAtlasDataMessage.h
  ../src/AboutPage/AboutPageIndoorPositionSettingsMessage.cpp
  ../src/AboutPage/AboutPageIndoorPositionSettingsMessage.h
  ../src/AboutPage/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\AboutPage FILES ${currsources})
include(../src/AboutPage/View/CMakeLists.txt)
