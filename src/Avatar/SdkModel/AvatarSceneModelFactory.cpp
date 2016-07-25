// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AvatarSceneModelFactory.h"

#include <fstream>

#include "PODMaterial.h"
#include "PODFile.h"
#include "PODFileParser.h"
#include "PODScene.h"
#include "SceneModel.h"
#include "SceneModelAnimator.h"
#include "SceneModelFactory.h"
#include "Types.h"

#include "XrayAnimatedSceneModel.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {            
            
            AvatarSceneModelFactory::AvatarSceneModelFactory(const Eegeo::Modules::Core::SceneModelsModule& sceneModelsModule, Eegeo::Helpers::IFileIO& fileIO)
            : m_sceneModelsModule(sceneModelsModule)
            , m_fileIO(fileIO)
            {
                
            }
            
            IAnimatedSceneModel* AvatarSceneModelFactory::CreateModel(const std::string& fileName,
                                                                    const Eegeo::Rendering::LayerIds::Values& renderingLayer)
            {
                const u32 fps = 30;
                Eegeo::Rendering::SceneModels::SceneModelFactory& sceneModelFactory = m_sceneModelsModule.GetLocalSceneModelFactory();
                
                //Load POD file
                size_t size;
                std::fstream stream;
                bool success = m_fileIO.OpenFile(stream, size, fileName, std::ifstream::in | std::ifstream::binary);
                Eegeo_ASSERT(success, "Avatar Model file must exist");
                const Eegeo::IO::POD::PODFile* pPODfile = Eegeo::IO::POD::PODFileParser::ParseFileFromPODStream(stream, (u32)size);// sohail typecast u32
                const Eegeo::IO::POD::PODScene* pPODScene = pPODfile->GetScene(0);
                Eegeo_ASSERT(pPODScene != NULL, "Avatar Model PODFile must have scene 0");
                
                //Regular Model and Animator creation
                Eegeo::Rendering::SceneModels::SceneModel* pModel = sceneModelFactory.CreateSceneModelFromPodScene(*pPODScene, fileName, "");
                pModel->SetLayer(renderingLayer);
                Eegeo::Rendering::SceneModels::SceneModelAnimator* pAnimator = Eegeo_NEW(Eegeo::Rendering::SceneModels::SceneModelAnimator)(*pModel, fps);
                
                
                IAnimatedSceneModel* animatedModel = Eegeo_NEW(XrayAnimatedSceneModel)(pModel, pAnimator);
                
                return animatedModel;
            }
        }
    }
}