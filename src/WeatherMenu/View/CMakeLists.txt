set(headers ${headers} src/WeatherMenu/View
)
set(currsources
  src/WeatherMenu/View/WeatherMenuStateOption.cpp
  src/WeatherMenu/View/WeatherMenuStateOption.h
)
set(sources ${sources} ${currsources})
source_group(\\WeatherMenu\\View FILES ${currsources})
