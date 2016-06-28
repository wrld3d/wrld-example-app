// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WeatherController.h"
#include "IVisualMapService.h"
#include "VisualMapState.h"

#include <algorithm>
#include <utility>
#include <iterator>

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace SdkModel
        {
            namespace
            {
                typedef std::pair<std::string, std::string> TTimeWeatherPair;
                TTimeWeatherPair ExtractTimeWeatherPairFromState(const std::string& state)
                {
                    std::string::const_reverse_iterator iter = std::find_if(state.rbegin(), state.rend(), ::isupper);
                    size_t index = state.size() - std::distance(state.rbegin(), iter) - 1;
                    
                    const std::string& time = state.substr(0, index);
                    const std::string& weather = state.substr(index);
                    
                    return std::make_pair(time, weather);
                }
            }
            
            WeatherController::WeatherController(VisualMap::SdkModel::IVisualMapService& visualMapService)
            : m_visualMapService(visualMapService)
            {
            }

            void WeatherController::SetTime(const std::string& time)
            {
                const VisualMap::SdkModel::VisualMapState& currentState = m_visualMapService.GetCurrentVisualMapState();
                const TTimeWeatherPair& currentTimeWeather = ExtractTimeWeatherPairFromState(currentState.GetState());
                SetState(time + currentTimeWeather.second);
            }

            void WeatherController::SetWeather(const std::string& weather)
            {
                const VisualMap::SdkModel::VisualMapState& currentState = m_visualMapService.GetCurrentVisualMapState();
                const TTimeWeatherPair& currentTimeWeather = ExtractTimeWeatherPairFromState(currentState.GetState());
                SetState(currentTimeWeather.first + weather);
            }

            void WeatherController::SetTheme(const std::string& theme)
            {
                m_visualMapService.SetVisualMapTheme(theme);
            }
            
            void WeatherController::SetState(const std::string& state)
            {
                m_visualMapService.SetVisualMapThemeState(state);
            }
        }
    }
}
