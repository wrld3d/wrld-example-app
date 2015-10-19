// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorsCustomMaterialParser.h"
#include "InteriorsCustomMaterialDto.h"
#include "CubeFaceFileNames.h"
#include "InteriorMaterialSemantics.h"
#include "LayerIds.h"
#include "InteriorsCustomMaterialKeys.h"


#include "document.h"
namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {
            namespace
            {
                std::vector<InteriorsCustomTextureDto> ParseTextures(const rapidjson::Document& customMaterialJson)
                {
                    std::vector<InteriorsCustomTextureDto> result;
                    if (customMaterialJson.HasMember(InteriorsCustomMaterialKeys::Textures.c_str()))
                    {
                        const rapidjson::Value& texturesJson = customMaterialJson[InteriorsCustomMaterialKeys::Textures.c_str()];
                        
                        int textureCount = texturesJson.Size();
                        result.reserve(textureCount);
                        for (int i = 0; i < textureCount; ++i)
                        {
                            const rapidjson::Value& textureJson = texturesJson[i];
                            InteriorsCustomTextureDto textureDto;
                            textureDto.textureKey = textureJson[InteriorsCustomMaterialKeys::TextureKey.c_str()].GetString();
                            textureDto.filename = textureJson[InteriorsCustomMaterialKeys::Filename.c_str()].GetString();
                            result.push_back(textureDto);
                        }
                        
                    }
                    
                    return result;
                }
                
                std::vector<InteriorsCustomCubeMapTextureDto> ParseCubeMapTextures(const rapidjson::Document& customMaterialJson)
                {
                    std::vector<InteriorsCustomCubeMapTextureDto> result;
                    if (customMaterialJson.HasMember(InteriorsCustomMaterialKeys::CubeMapTextures.c_str()))
                    {
                        const rapidjson::Value& texturesJson = customMaterialJson[InteriorsCustomMaterialKeys::CubeMapTextures.c_str()];
                        
                        int textureCount = texturesJson.Size();
                        result.reserve(textureCount);
                        for (int i = 0; i < textureCount; ++i)
                        {
                            const rapidjson::Value& textureJson = texturesJson[i];
                            InteriorsCustomCubeMapTextureDto dto;
                            dto.textureKey = textureJson[InteriorsCustomMaterialKeys::TextureKey.c_str()].GetString();
                            dto.positiveXFilename = textureJson["PositiveXFilename"].GetString();
                            dto.negativeXFilename = textureJson["NegativeXFilename"].GetString();
                            dto.positiveYFilename = textureJson["PositiveYFilename"].GetString();
                            dto.negativeYFilename = textureJson["NegativeYFilename"].GetString();
                            dto.positiveZFilename = textureJson["PositiveZFilename"].GetString();
                            dto.negativeZFilename = textureJson["NegativeZFilename"].GetString();
                            
                            
                            result.push_back(dto);
                        }
                        
                    }
                    
                    return result;
                }
                
                void TryAddString(const std::string& key, const rapidjson::Value& materialJson, std::vector<std::pair<std::string, std::string> >& inout_strings)
                {
                    if (materialJson.HasMember(key.c_str()))
                    {
                        inout_strings.push_back(std::make_pair(key, materialJson[key.c_str()].GetString()));
                    }
                }
                
                void TryAddColor(const std::string& key, const rapidjson::Value& materialJson, std::vector<std::pair<std::string, Eegeo::v4> >& inout_colors)
                {
                    if (materialJson.HasMember(key.c_str()))
                    {
                        const rapidjson::Value& jsonValue = materialJson[key.c_str()];
                        Eegeo_ASSERT(jsonValue.IsArray());
                        Eegeo_ASSERT(jsonValue.Size() == 4);
                        
                        Eegeo::v4 color;
                        int indexR = 0;
                        int indexG = 1;
                        int indexB = 2;
                        int indexA = 3;
                        
                        color.x = static_cast<float>(jsonValue[indexR].GetDouble());
                        color.y = static_cast<float>(jsonValue[indexG].GetDouble());
                        color.z = static_cast<float>(jsonValue[indexB].GetDouble());
                        color.w = static_cast<float>(jsonValue[indexA].GetDouble());
                        
                        inout_colors.push_back(std::make_pair(key, color));
                    }
                }
                
                void TryAddScalar(const std::string& key, const rapidjson::Value& materialJson, std::vector<std::pair<std::string, float> >& inout_scalars)
                {
                    if (materialJson.HasMember(key.c_str()))
                    {
                        const float value = static_cast<float>(materialJson[key.c_str()].GetDouble());
                        inout_scalars.push_back(std::make_pair(key, value));
                    }
                }
                
                InteriorsCustomMaterialDto ParseMaterial(const rapidjson::Value& materialJson)
                {
                    using namespace Eegeo::Resources::Interiors::InteriorMaterialSemantics;
                    
                    InteriorsCustomMaterialDto result;
                    
                    
                    result.materialName = materialJson[InteriorsCustomMaterialKeys::MaterialName.c_str()].GetString();
                    
                    TryAddString(InteriorsCustomMaterialKeys::MaterialType.c_str(), materialJson, result.keyValueStrings);
                    TryAddString(DiffuseTexture, materialJson, result.keyValueStrings);
                    TryAddString(CubeMapTexture, materialJson, result.keyValueStrings);
                    
                    TryAddColor(DiffuseColor, materialJson, result.keyValueColors);
                    TryAddColor(SpecularColor, materialJson, result.keyValueColors);
                    TryAddColor(ReflectionColor, materialJson, result.keyValueColors);
                    TryAddColor(AmbientColor, materialJson, result.keyValueColors);
                    
                    TryAddScalar(SpecularPowerScalar, materialJson, result.keyValueScalars);
                    TryAddScalar(SpecularModulateTextureScalar, materialJson, result.keyValueScalars);
                    TryAddScalar(SpecularityFromTextureLuminanceScalar, materialJson, result.keyValueScalars);
                    
                    return result;
                }
                
                std::vector<InteriorsCustomMaterialDto> ParseMaterialDtos(const rapidjson::Document& customMaterialJson)
                {
                    std::vector<InteriorsCustomMaterialDto> result;
                    
                    if (customMaterialJson.HasMember(InteriorsCustomMaterialKeys::Materials.c_str()))
                    {
                        const rapidjson::Value& materialsJson = customMaterialJson[InteriorsCustomMaterialKeys::Materials.c_str()];
                        
                        int materialCount = materialsJson.Size();
                        result.reserve(materialCount);
                        for (int i = 0; i < materialCount; ++i)
                        {
                            const rapidjson::Value& materialJson = materialsJson[i];
                            
                            const InteriorsCustomMaterialDto& materialDto = ParseMaterial(materialJson);
                            result.push_back(materialDto);
                        }
                    }
                    
                    return result;
                }
            }
            
            InteriorsCustomMaterialParserResult InteriorsCustomMaterialParser::Parse(const std::string& materialsJson) const
            {
                rapidjson::Document document;
                if (document.Parse<0>(materialsJson.c_str()).HasParseError())
                {
                    Eegeo_ASSERT(false, "Error parsing materials josn");
                }
                
                
                InteriorsCustomMaterialParserResult result;
                
                result.textureDtos = ParseTextures(document);
                
                result.cubeMapTextureDtos = ParseCubeMapTextures(document);
                
                result.materialDtos = ParseMaterialDtos(document);

                return result;

            }
            
            
        }
    }
}