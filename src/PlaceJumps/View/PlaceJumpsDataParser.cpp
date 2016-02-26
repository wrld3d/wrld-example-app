// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PlaceJumpsDataParser.h"
#include "document.h"
#include "error/en.h"
#include "LatLongAltitude.h"
#include "Logger.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace View
        {
            namespace PlaceJumpsDataParser
            {
                bool ParsePlaceJumps(const std::string &json, std::vector<PlaceJumpModel>& out_placeJumpModel)
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
                        double latitude = jsonValue["Latitude"].GetDouble();
                        double longitude = jsonValue["Longitude"].GetDouble();
                        float headingDegrees = static_cast<float>(jsonValue["HeadingDegrees"].GetDouble());
                        float distance = static_cast<float>(jsonValue["Distance"].GetDouble());
                        Eegeo_ASSERT(jsonValue.HasMember("Icon"), "Placejump definition error: Place %s has no icon defined.", name.c_str());

                        std::string icon = jsonValue["Icon"].GetString();

                        PlaceJumpModel jump(name, Eegeo::Space::LatLong::FromDegrees(latitude, longitude), headingDegrees, distance, icon);
                        out_placeJumpModel.push_back(jump);
                    }

                    return true;
                }
            }
        }
    }
}
