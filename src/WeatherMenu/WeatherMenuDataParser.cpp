// Copyright eeGeo Ltd (2012-2014), All Rights Reserved


#include "WeatherMenuDataParser.h"
#include "document.h"
#include "Logger.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace WeatherMenuDataParser
        {
            bool ParseWeatherStates(const std::string& json, std::vector<WeatherMenuStateModel>&  out_weatherStates)
            {
                rapidjson::Document document;
                if(document.Parse<0>(json.c_str()).HasParseError())
                {
                    EXAMPLE_LOG("JSON ERROR: %s/n", document.GetParseError());
                    return false;
                }
                
                int numJumps = document.Size();
                for(int i = 0; i < numJumps; i++)
                {
                    const rapidjson::Value& jsonValue = document[i];
                    
                    std::string name = jsonValue["Name"].GetString();

                    std::string time = jsonValue.HasMember("Time") ? jsonValue["Time"].GetString() : "";
                    std::string weather = jsonValue.HasMember("Weather") ? jsonValue["Weather"].GetString() : "";
                    std::string season = jsonValue.HasMember("Season") ? jsonValue["Season"].GetString() : "";

                    Eegeo_ASSERT(jsonValue.HasMember("Icon"), "Weather configuration error: State %s has no icon defined.", name.c_str());
                    std::string icon = jsonValue["Icon"].GetString();
                    
                    WeatherMenuStateModel weatherState(name, time, weather, season, icon);
                    out_weatherStates.push_back(weatherState);
                }
                
                return true;

            }
        }
    }
}
