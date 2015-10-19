// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorsCustomMaterialsModule.h"
#include "InteriorsCustomMaterialFactory.h"
#include "InteriorsStreamingModule.h"
#include "InteriorsCustomMaterialDto.h"
#include "IFileIO.h"
#include "IInteriorsTextureResourceService.h"
#include "InteriorsCustomMaterialDtoRepository.h"
#include "CubeFaceFileNames.h"
#include "InteriorMaterialSemantics.h"
#include "LayerIds.h"
#include "InteriorsCustomMaterialParser.h"



#include <vector>

namespace ExampleApp
{
    namespace InteriorsCustomMaterials
    {
        namespace SdkModel
        {
            namespace
            {
                InteriorsCustomMaterialParserResult ParseCustomMaterials(Eegeo::Helpers::IFileIO& fileIO, const std::string& filename)
                {
                    std::fstream stream;
                    size_t size;
                    
                    if(!fileIO.OpenFile(stream, size, filename))
                    {
                        Eegeo_ASSERT(false, "Failed to load %s.", filename.c_str());
                    }
                    
                    std::string json((std::istreambuf_iterator<char>(stream)),
                                     (std::istreambuf_iterator<char>()));
                    
                    InteriorsCustomMaterialParser parser;
                    
                    const InteriorsCustomMaterialParserResult& result = parser.Parse(json);
                    return result;
                }

                
                void CreateAndRegisterTextures(const std::vector<InteriorsCustomTextureDto>& customTextureDtos, Eegeo::Resources::Interiors::IInteriorsTextureResourceService& interiorsTextureResourceService)
                {
                    for (std::vector<InteriorsCustomTextureDto>::const_iterator iter = customTextureDtos.begin(); iter != customTextureDtos.end(); ++iter)
                    {
                        const InteriorsCustomTextureDto& textureDto = *iter;
                        
                        interiorsTextureResourceService.Create(textureDto.textureKey, textureDto.filename);
                    }
                }
                
                void CreateAndRegisterCubeMapTextures(const std::vector<InteriorsCustomCubeMapTextureDto>& customTextureDtos, Eegeo::Resources::Interiors::IInteriorsTextureResourceService& interiorsTextureResourceService)
                {
                    for (std::vector<InteriorsCustomCubeMapTextureDto>::const_iterator iter = customTextureDtos.begin(); iter != customTextureDtos.end(); ++iter)
                    {
                        const InteriorsCustomCubeMapTextureDto& textureDto = *iter;
                        
                        Eegeo::Helpers::CubeFaceFileNames cubeFaceFileNames;
                        cubeFaceFileNames.positiveXFileName = textureDto.positiveXFilename;
                        cubeFaceFileNames.negativeXFileName = textureDto.negativeXFilename;
                        cubeFaceFileNames.positiveYFileName = textureDto.positiveYFilename;
                        cubeFaceFileNames.negativeYFileName = textureDto.negativeYFilename;
                        cubeFaceFileNames.positiveZFileName = textureDto.positiveZFilename;
                        cubeFaceFileNames.negativeZFileName = textureDto.negativeZFilename;
                        
                        interiorsTextureResourceService.CreateFromCubeMapFaces(textureDto.textureKey, cubeFaceFileNames);
                    }
                }

                void RegisterMaterialData(const std::vector<InteriorsCustomMaterialDto>& materialDtos, IInteriorsCustomMaterialDtoRepository& materialDtoRepository)
                {
                    for (std::vector<InteriorsCustomMaterialDto>::const_iterator iter = materialDtos.begin(); iter != materialDtos.end(); ++iter)
                    {
                        const InteriorsCustomMaterialDto materialDto = *iter;

                        materialDtoRepository.Add(*iter);
                    }
                }
            }

            InteriorsCustomMaterialsModule::InteriorsCustomMaterialsModule(Eegeo::Modules::Map::Layers::InteriorsStreamingModule& interiorsStreamingModule,
                                                                           
                                                                           Eegeo::Helpers::IFileIO& fileIO)
            : m_pInteriorsCustomMaterialFactory(NULL)
            , m_pInteriorsCustomMaterialDtoRepository(NULL)
            {
                m_pInteriorsCustomMaterialDtoRepository = Eegeo_NEW(InteriorsCustomMaterialDtoRepository)();
                
            
                m_pInteriorsCustomMaterialFactory = Eegeo_NEW(InteriorsCustomMaterialFactory)(*m_pInteriorsCustomMaterialDtoRepository,
                                                                                              interiorsStreamingModule.GetInteriorsMaterialFactory(),
                                                                                              interiorsStreamingModule.GetInteriorsDiffuseTexturedMaterialFactory(),
                                                                                              interiorsStreamingModule.GetInteriorsDiffuseSpecularMaterialFactory(),
                                                                                              interiorsStreamingModule.GetInteriorsCubeMappedMaterialFactory()
                                                                                              );
                
                interiorsStreamingModule.AddInteriorsMaterialFactory(m_pInteriorsCustomMaterialFactory);
                
                const InteriorsCustomMaterialParserResult& materialParserResult = ParseCustomMaterials(fileIO, "Interiors/interior_materials.json");
                
                CreateAndRegisterTextures(materialParserResult.textureDtos, interiorsStreamingModule.GetInteriorsTextureResourceService());
                
                CreateAndRegisterCubeMapTextures(materialParserResult.cubeMapTextureDtos, interiorsStreamingModule.GetInteriorsTextureResourceService());
                
                RegisterMaterialData(materialParserResult.materialDtos, *m_pInteriorsCustomMaterialDtoRepository);
            }
            
            InteriorsCustomMaterialsModule::~InteriorsCustomMaterialsModule()
            {
                Eegeo_DELETE m_pInteriorsCustomMaterialFactory;
                Eegeo_DELETE m_pInteriorsCustomMaterialDtoRepository;
            }
           
        }
    }
}