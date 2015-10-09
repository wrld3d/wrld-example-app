// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorsCustomMaterialsModule.h"
#include "InteriorsCustomMaterialFactory.h"
#include "InteriorsStreamingModule.h"
#include "InteriorsCustomMaterialDto.h"
#include "IFileIO.h"
#include "IInteriorsTextureResourceService.h"

#include "document.h"

#include <vector>

namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {
            namespace
            {
                std::vector<InteriorsCustomMaterialDto> ParseCustomMaterials(Eegeo::Helpers::IFileIO& fileIO, const std::string& filename)
                {
                    std::vector<InteriorsCustomMaterialDto> result;
                    std::fstream stream;
                    size_t size;
                    
                    if(!fileIO.OpenFile(stream, size, filename))
                    {
                        Eegeo_ASSERT(false, "Failed to load %s.", filename.c_str());
                    }
                    
                    std::string json((std::istreambuf_iterator<char>(stream)),
                                     (std::istreambuf_iterator<char>()));
                    
                    rapidjson::Document document;
                    if(document.Parse<0>(json.c_str()).HasParseError())
                    {
                        Eegeo_ASSERT(false, "Error parsing %s.", filename.c_str());
                    }
                    
                    int elementCount = document.Size();
                    for (int i = 0; i < elementCount; ++i)
                    {
                        const rapidjson::Value& jsonValue = document[i];
                        
                        InteriorsCustomMaterialDto materialDto;
                        materialDto.materialName = jsonValue["MaterialName"].GetString();
                        materialDto.materialType = jsonValue["MaterialType"].GetString();
                        
                        
                        const rapidjson::Value& jsonTexturesValue = jsonValue["Textures"];
                        int textureCount = jsonTexturesValue.Size();
                        for (int j = 0; j < textureCount; ++j)
                        {
                            const rapidjson::Value& jsonTextureValue = jsonTexturesValue[j];
                            InteriorsCustomTextureDto textureDto;
                            textureDto.textureKey = jsonTextureValue["TextureKey"].GetString();
                            textureDto.filename = jsonTextureValue["Filename"].GetString();
                            materialDto.textures.push_back(textureDto);
                        }
                        
                        
                        result.push_back(materialDto);
                    }
                    
                    return result;
                }
                
                void CreateAndRegisterTextures(const std::vector<InteriorsCustomMaterialDto>& customMaterialDtos, Eegeo::Resources::Interiors::IInteriorsTextureResourceService& interiorsTextureResourceService)
                {
                
                    for (std::vector<InteriorsCustomMaterialDto>::const_iterator iter = customMaterialDtos.begin(); iter != customMaterialDtos.end(); ++iter)
                    {
                        const InteriorsCustomMaterialDto& materialDto = *iter;
                        
                        for (std::vector<InteriorsCustomTextureDto>::const_iterator texIter = materialDto.textures.begin(); texIter != materialDto.textures.end(); ++texIter)
                        {
                            const InteriorsCustomTextureDto& textureDto = *texIter;
                            
                            interiorsTextureResourceService.Create(textureDto.textureKey, textureDto.filename);
                        }
                    }
                    
                }
                
                InteriorsCustomMaterialFactory::TMaterialKeyToFactoryType MakeMaterialFactoryMap(const std::vector<InteriorsCustomMaterialDto>& customMaterialDtos)
                {
                    InteriorsCustomMaterialFactory::TMaterialKeyToFactoryType materialKeyToFactoryType;
                    
                    for (std::vector<InteriorsCustomMaterialDto>::const_iterator iter = customMaterialDtos.begin(); iter != customMaterialDtos.end(); ++iter)
                    {
                        const InteriorsCustomMaterialDto& materialDto = *iter;
                        
                        materialKeyToFactoryType.insert(std::make_pair(materialDto.materialName, materialDto.materialType));
                    }
                    
                    return materialKeyToFactoryType;
                }
            }

            InteriorsCustomMaterialsModule::InteriorsCustomMaterialsModule(Eegeo::Modules::Map::Layers::InteriorsStreamingModule& interiorsStreamingModule,
                                                                           
                                                                           Eegeo::Helpers::IFileIO& fileIO)
            : m_pInteriorsCustomMaterialFactory(NULL)
            {
                const std::vector<InteriorsCustomMaterialDto>& customMaterialDtos = ParseCustomMaterials(fileIO, "Interiors/interior_materials.json");
                
                
                CreateAndRegisterTextures(customMaterialDtos, interiorsStreamingModule.GetInteriorsTextureResourceService());
                
                
                const InteriorsCustomMaterialFactory::TMaterialKeyToFactoryType& materialKeyToFactoryType = MakeMaterialFactoryMap(customMaterialDtos);
                
                
            
            
                m_pInteriorsCustomMaterialFactory = Eegeo_NEW(InteriorsCustomMaterialFactory)(materialKeyToFactoryType,
                                                                                              interiorsStreamingModule.GetInteriorsMaterialFactory(),
                                                                                              interiorsStreamingModule.GetInteriorsDiffuseTexturedMaterialFactory()
                                                                                              );
                
                interiorsStreamingModule.AddInteriorsMaterialFactory(m_pInteriorsCustomMaterialFactory);
            }
            
            InteriorsCustomMaterialsModule::~InteriorsCustomMaterialsModule()
            {
                Eegeo_DELETE m_pInteriorsCustomMaterialFactory;
            }

            
            
        }
    }
}