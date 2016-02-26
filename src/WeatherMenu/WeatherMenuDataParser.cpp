// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WeatherMenuDataParser.h"
#include "error/en.h"
#include "document.h"
#include "Logger.h"

namespace ExampleApp
{
    namespace WeatherMenu
    {
        namespace WeatherMenuDataParser
        {
            bool ParseWeatherStates(const std::string& json, std::vector<SdkModel::WeatherMenuStateModel>&  out_weatherStates)
            {
                rapidjson::Document document;
                if(document.Parse<0>(json.c_str()).HasParseError())
                {
                    rapidjson::ParseErrorCode errorCode = document.GetParseError();
                    const char* errorMessage = rapidjson::GetParseError_En(errorCode);
                    EXAMPLE_LOG("JSON ERROR: (Code %d) %s/n", errorCode, errorMessage);
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
                    
                    std::string state = jsonValue.HasMember("State") ? jsonValue["State"].GetString() : "";

                    SdkModel::WeatherMenuStateModel weatherState(name, time, weather, season, icon, state);
                    out_weatherStates.push_back(weatherState);
                }

                return true;

            }
        }
    }
}
