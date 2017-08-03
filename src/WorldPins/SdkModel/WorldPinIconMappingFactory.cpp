// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinIconMappingFactory.h"
#include "WorldPinIconMapping.h"
#include "IFileIO.h"
#include "AtlasTexturePageLayout.h"
#include "ITextureFileLoader.h"
#include "GLHelpers.h"
#include "ImagePathHelpers.h"

#include "document.h"
#include <fstream>


namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            namespace
            {
                const std::string defaultKey = "pin";
                
                struct WorldPinIconMappingPage
                {
                    int width;
                    int height;
                    std::string filename;
                };

                struct WorldPinIconMappingIconDefinition
                {
                    int index;
                    std::string iconKey;
                    int x;
                    int y;
                    int width;
                    int height;
                    int page;
                };

                
                rapidjson::Document ParseIconMappingJson(const std::string& mappingJson)
                {
                    rapidjson::Document document;

                    const bool hasParseError = document.Parse<0>(mappingJson.c_str()).HasParseError();
                    Eegeo_ASSERT(!hasParseError, "error parsing icon mapping json");

                    return document;
                }

                std::vector<WorldPinIconMappingPage> ParsePages(const rapidjson::Value& json)
                {
                    size_t mappingsCount = json.Size();

                    std::vector<WorldPinIconMappingPage> pages;
                    pages.reserve(mappingsCount);

                    for (int i = 0; i < mappingsCount; ++i)
                    {
                        const rapidjson::Value& mappingJson = json[i];
                        Eegeo_ASSERT(mappingJson.HasMember("file"));
                        Eegeo_ASSERT(mappingJson.HasMember("width"));
                        Eegeo_ASSERT(mappingJson.HasMember("height"));

                        WorldPinIconMappingPage page;
                        page.filename = mappingJson["file"].GetString();
                        page.width = mappingJson["width"].GetInt();
                        page.height = mappingJson["height"].GetInt();

                        pages.push_back(page);
                    }

                    return pages;
                }

                std::vector<WorldPinIconMappingIconDefinition> ParseIcons(const rapidjson::Value& json)
                {
                    Eegeo_ASSERT(json.IsArray());
                    
                    size_t mappingsCount = json.Size();
                    
                    std::vector<WorldPinIconMappingIconDefinition> mappingEntries;
                    mappingEntries.reserve(mappingsCount);

                    for (int i = 0; i < mappingsCount; ++i)
                    {
                        const rapidjson::Value& mappingJson = json[i];

                        
                        Eegeo_ASSERT(mappingJson.HasMember("id"), "Icon definition has no id");
                        Eegeo_ASSERT(mappingJson.HasMember("index"), "Icon definition has no index");
                        Eegeo_ASSERT(mappingJson.HasMember("x"), "Icon definition has no x coordinate");
                        Eegeo_ASSERT(mappingJson.HasMember("y"), "Icon definition has no y coordinate");
                        Eegeo_ASSERT(mappingJson.HasMember("w"), "Icon definition has no width");
                        Eegeo_ASSERT(mappingJson.HasMember("h"), "Icon definition has no height");
                     
                        WorldPinIconMappingIconDefinition icon;
                        icon.iconKey = mappingJson["id"].GetString();
                        icon.index = mappingJson["index"].GetInt();
                        icon.x = mappingJson["x"].GetInt();
                        icon.y = mappingJson["y"].GetInt();
                        icon.width = mappingJson["w"].GetInt();
                        icon.height = mappingJson["h"].GetInt();
                                                
                        
                        mappingEntries.push_back(icon);
                    }
                    
                    return mappingEntries;
                }
                
            }
            
            WorldPinIconMappingFactory::WorldPinIconMappingFactory(Eegeo::Helpers::IFileIO& fileIO, 
                const std::string& sheetManifestFile, 
                Eegeo::Helpers::ITextureFileLoader& textureFileLoader)
            : m_fileIO(fileIO)
            , m_textureFileLoader(textureFileLoader)
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
                
                rapidjson::Document document = ParseIconMappingJson(json);

                Eegeo_ASSERT(document.HasMember("pages"));
                const rapidjson::Value& pageMappings = document["pages"];
                std::vector<WorldPinIconMappingPage> pages = ParsePages(pageMappings);

                Eegeo_ASSERT(document.HasMember("icons"));
                const rapidjson::Value& iconMappings = document["icons"];
                std::vector<WorldPinIconMappingIconDefinition> icons = ParseIcons(iconMappings);

                // Only using one page for now for expediency. Support for multiple page atlases will come later.
                Eegeo_ASSERT(pages.size()==1, "Only support single page mappings for pin icons currently");
                WorldPinIconMappingPage page = pages.at(0);

                const std::string filename = page.filename;
                const int width = page.width;
                const int height = page.height;

                Eegeo::Helpers::GLHelpers::TextureInfo texturePage;
                Eegeo::Rendering::AtlasTexturePageLayout* pTextureAtlas = Eegeo_NEW(Eegeo::Rendering::AtlasTexturePageLayout)(width, height, true);

                std::string filepath = "SearchResultOnMap/";
                filepath.append(filename);
                
                if (!m_textureFileLoader.LoadTexture(texturePage, Helpers::ImageHelpers::GetImageNameForDevice(filepath, ".png")))
                {
                    Eegeo_ASSERT(false, "Failed to load texture for pins: %s", filepath.c_str());
                }

                std::map<std::string, int> keyToIconIndex;
                for (std::vector<WorldPinIconMappingIconDefinition>::const_iterator it = icons.begin(); it != icons.end(); it++)
                {
                    const WorldPinIconMappingIconDefinition iconDef = *it;

                    Eegeo::Geometry::Bounds2D coordinates(Eegeo::v2(iconDef.x, iconDef.y), Eegeo::v2(iconDef.x + iconDef.width, iconDef.y + iconDef.height));
                    pTextureAtlas->AddSprite(iconDef.index, coordinates);

                    keyToIconIndex[iconDef.iconKey] = iconDef.index;
                }
                
                return Eegeo_NEW(WorldPinIconMapping)(defaultKey, texturePage, pTextureAtlas, keyToIconIndex);
            }
        }
    }
}