set(headers ${headers} ../src/WeatherMenu
)
set(currsources
  ../src/WeatherMenu/CMakeLists.txt
  ../src/WeatherMenu/WeatherMenu.h
  ../src/WeatherMenu/WeatherMenuDataParser.cpp
  ../src/WeatherMenu/WeatherMenuDataParser.h
  ../src/WeatherMenu/WeatherSelectedMessage.cpp
  ../src/WeatherMenu/WeatherSelectedMessage.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\WeatherMenu FILES ${currsources})
include(../src/WeatherMenu/SdkModel/CMakeLists.txt)
include(../src/WeatherMenu/View/CMakeLists.txt)
