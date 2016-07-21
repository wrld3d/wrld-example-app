// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinIconMappingFactory.h"
#include "WorldPinIconMapping.h"
#include "IFileIO.h"

#include "document.h"
#include <string>
#include <fstream>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            namespace
            {
                const std::string defaultKey = "misc";
                
                
                std::vector<std::pair<std::string, int> > ParseIconMappingJson(const std::string& mappingJson)
                {
                    rapidjson::Document document;
                    
                    std::vector<std::pair<std::string, int> > mappingEntries;
                    
                    const bool hasParseError = document.Parse<0>(mappingJson.c_str()).HasParseError();
                    Eegeo_ASSERT(!hasParseError, "error parsing icon mapping json");
                    
                    Eegeo_ASSERT(document.HasMember("icons"));
                    const rapidjson::Value& iconMappings = document["icons"];
                    size_t mappingsCount = iconMappings.Size();
                    
                    mappingEntries.reserve(mappingsCount);

                    for (int i = 0; i < mappingsCount; ++i)
                    {
                        const rapidjson::Value& mappingJson = iconMappings[i];
                        Eegeo_ASSERT(mappingJson.HasMember("name"));
                        Eegeo_ASSERT(mappingJson.HasMember("index"));
                        
                        const std::string& iconKey = mappingJson["name"].GetString();
                        const int iconIndex = mappingJson["index"].GetInt();
                        
                        mappingEntries.push_back(std::make_pair(iconKey, iconIndex));
                    }
                    
                    return mappingEntries;
                }
                
            }
            
            WorldPinIconMappingFactory::WorldPinIconMappingFactory(Eegeo::Helpers::IFileIO& fileIO, const std::string& sheetManifestFile)
            : m_fileIO(fileIO)
            , m_sheetManifestFile(sheetManifestFile)
            {

            }
            
            IWorldPinIconMapping* WorldPinIconMappingFactory::Create() const
            {
                std::fstream stream;
                size_t size;
                
                if(!m_fileIO.OpenFile(stream, size, m_sheetManifestFile))
                {
                    Eegeo_ASSERT(false, "Failed to load pin sheet definitions file.");
                }
                
                std::string json((std::istreambuf_iterator<char>(stream)),
                                 (std::istreambuf_iterator<char>()));
                
                const std::vector<std::pair<std::string, int> >& keyIconIndexPairs = ParseIconMappingJson(json);
                
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