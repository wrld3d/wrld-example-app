// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GeoNamesJsonParser.h"

#include <sstream>
#include "document.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                void GeoNamesJsonParser::ParseGeoNamesQueryResults(const std::string& serialized,
                                                                   std::vector<GeoNamesSearchResultDto>& out_results)
                {
                    rapidjson::Document document;
                    
                    if (!document.Parse<0>(serialized.c_str()).HasParseError())
                    {
                        if(document.HasMember("geonames"))
                        {
                            const rapidjson::Value& entries = document["geonames"];
                            size_t numEntries = entries.Size();
                            
                            for(int i = 0; i < numEntries; ++i)
                            {
                                const rapidjson::Value& json = entries[i];
                                
                                // Note: The GeoNames API returns the latitude and longitude as strings instead of numeric properties.
                                const double lat(::atof(json["lat"].GetString()));
                                const double lng(::atof(json["lng"].GetString()));
                                
                                std::stringstream ss;
                                ss << json["geonameId"].GetInt();
                                
                                GeoNamesSearchResultDto dto(ss.str(),
                                                            json["name"].GetString(),
                                                            json["countryName"].GetString(),
                                                            Eegeo::Space::LatLong::FromDegrees(lat, lng),
                                                            json["population"].GetInt());
                                
                                out_results.push_back(dto);
                            }
                        }
                    }
                }
            }
        }
    }
}
