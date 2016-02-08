set(headers ${headers} ../src/WeatherMenu/View
)
set(currsources
  ../src/WeatherMenu/View/CMakeLists.txt
  ../src/WeatherMenu/View/WeatherMenuStateOption.cpp
  ../src/WeatherMenu/View/WeatherMenuStateOption.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\WeatherMenu\\View FILES ${currsources})
