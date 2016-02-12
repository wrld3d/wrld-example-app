set(headers ${headers} ../src/WeatherMenu/SdkModel
)
set(currsources
  ../src/WeatherMenu/SdkModel/CMakeLists.txt
  ../src/WeatherMenu/SdkModel/IWeatherController.h
  ../src/WeatherMenu/SdkModel/IWeatherMenuModule.h
  ../src/WeatherMenu/SdkModel/IWeatherMenuStateModel.h
  ../src/WeatherMenu/SdkModel/WeatherController.cpp
  ../src/WeatherMenu/SdkModel/WeatherController.h
  ../src/WeatherMenu/SdkModel/WeatherMenuModule.cpp
  ../src/WeatherMenu/SdkModel/WeatherMenuModule.h
  ../src/WeatherMenu/SdkModel/WeatherMenuStateModel.cpp
  ../src/WeatherMenu/SdkModel/WeatherMenuStateModel.h
  ../src/WeatherMenu/SdkModel/WeatherSelectedMessageHandler.cpp
  ../src/WeatherMenu/SdkModel/WeatherSelectedMessageHandler.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\WeatherMenu\\SdkModel FILES ${currsources})
