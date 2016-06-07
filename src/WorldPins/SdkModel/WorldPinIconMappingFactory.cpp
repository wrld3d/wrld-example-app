// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinIconMappingFactory.h"
#include "WorldPinIconMapping.h"


#include "document.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            namespace
            {
                const std::string iconMappingsJson =
                "{"
                "    \"Mappings\": ["
                "    {"
                "        \"IconKey\": \"accommodation\","
                "        \"IconIndex\": 1"
                "    },"
                "    {"
                "        \"IconKey\": \"art_museums\","
                "        \"IconIndex\": 2"
                "    },"
                "    {"
                "       \"IconKey\": \"business\","
                "        \"IconIndex\": 3"
                "    },"
                "    {"
                "        \"IconKey\": \"entertainment\","
                "        \"IconIndex\": 4"
                "    },"
                "    {"
                "        \"IconKey\": \"food_drink\","
                "        \"IconIndex\": 5"
                "    },"
                "    {"
                "        \"IconKey\": \"amenities\","
                "        \"IconIndex\": 6"
                "    },"
                "    {"
                "        \"IconKey\": \"health\","
                "        \"IconIndex\": 7"
                "    },"
                "    {"
                "        \"IconKey\": \"shopping\","
                "        \"IconIndex\": 8"
                "    },"
                "    {"
                "        \"IconKey\": \"sports_leisure\","
                "        \"IconIndex\": 9"
                "    },"
                "    {"
                "        \"IconKey\": \"tourism\","
                "        \"IconIndex\": 10"
                "    },"
                "    {"
                "        \"IconKey\": \"transport\","
                "        \"IconIndex\": 11"
                "    },"
                "    {"
                "        \"IconKey\": \"place\","
                "        \"IconIndex\": 12"
                "    },"
                "    {"
                "        \"IconKey\": \"my_pins\","
                "        \"IconIndex\": 13"
                "    },"
                "    {"
                "        \"IconKey\": \"misc\","
                "        \"IconIndex\": 12"
                "    },"
                "    {"
                "        \"IconKey\": \"default\","
                "        \"IconIndex\": 12"
                "    },"
                "    {"
                "        \"IconKey\": \"person\","
                "        \"IconIndex\": 13"
                "    },"
                "    {"
                "        \"IconKey\": \"indoor_map_entry\","
                "        \"IconIndex\": 15"
                "    },"
                "    {"
                "        \"IconKey\": \"stationery\","
                "        \"IconIndex\": 20"
                "    },"
                "    {"
                "        \"IconKey\": \"toilets\","
                "        \"IconIndex\": 21"
                "    },"
                "    {"
                "        \"IconKey\": \"print_station\","
                "        \"IconIndex\": 22"
                "    },"
                "    {"
                "        \"IconKey\": \"emergency_exit\","
                "        \"IconIndex\": 20"
                "    },"
                "    {"
                "        \"IconKey\": \"tour_entry\","
                "        \"IconIndex\": 90"
                "    },"
                "    {"
                "        \"IconKey\": \"feed_twitter\","
                "        \"IconIndex\": 91"
                "    },"
                "    {"
                "        \"IconKey\": \"feed_you_tube\","
                "        \"IconIndex\": 92"
                "    },"
                "    {"
                "        \"IconKey\": \"feed_facebook\","
                "        \"IconIndex\": 93"
                "    },"
                "    {"
                "        \"IconKey\": \"feed_weblink\","
                "        \"IconIndex\": 94"
                "    },"
                "    {"
                "        \"IconKey\": \"feed_wikipedia\","
                "        \"IconIndex\": 95"
                "    },"
                "    {"
                "        \"IconKey\": \"feed_vimeo\","
                "        \"IconIndex\": 96"
                "    },"
                "    {"
                "        \"IconKey\": \"feed_google_plus\","
                "        \"IconIndex\": 97"
                "    },"
                "    {"
                "        \"IconKey\": \"feed_picasa\","
                "        \"IconIndex\": 98"
                "    }"
                "    ]"
                "}";
                
                
                const std::string defaultKey = "default";
                
                
                std::vector<std::pair<std::string, int> > ParseIconMappingJson(const std::string& mappingJson)
                {
                    rapidjson::Document document;
                    
                    std::vector<std::pair<std::string, int> > mappingEntries;
                    
                    const bool hasParseError = document.Parse<0>(mappingJson.c_str()).HasParseError();
                    Eegeo_ASSERT(!hasParseError, "error parsing icon mapping json");
                    
                    Eegeo_ASSERT(document.HasMember("Mappings"));
                    const rapidjson::Value& mappings = document["Mappings"];
                    size_t mappingsCount = mappings.Size();
                    
                    mappingEntries.reserve(mappingsCount);
                    
                    for (int i = 0; i < mappingsCount; ++i)
                    {
                        const rapidjson::Value& mappingJson = mappings[i];
                        Eegeo_ASSERT(mappingJson.HasMember("IconKey"));
                        Eegeo_ASSERT(mappingJson.HasMember("IconIndex"));
                        
                        const std::string& iconKey = mappingJson["IconKey"].GetString();
                        const int iconIndex = mappingJson["IconIndex"].GetInt();
                        
                        mappingEntries.push_back(std::make_pair(iconKey, iconIndex));
                    }
                    
                    return mappingEntries;
                }
                
            }
            
            WorldPinIconMappingFactory::WorldPinIconMappingFactory()
            {

            }
            
            IWorldPinIconMapping* WorldPinIconMappingFactory::Create() const
            {
                const std::vector<std::pair<std::string, int> >& keyIconIndexPairs = ParseIconMappingJson(iconMappingsJson);
                
                std::map<std::string, int> keyToIconIndex;
                
                for (std::vector<std::pair<std::string, int> >::const_iterator iter = keyIconIndexPairs.begin();
                     iter != keyIconIndexPairs.end();
                     ++iter)
                {
                    keyToIconIndex.insert(*iter);
                }
                
                return Eegeo_NEW(WorldPinIconMapping)(defaultKey, keyToIconIndex);
            }
        }
    }
}