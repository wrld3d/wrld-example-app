// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AvatarModule.h"

#include "InteriorId.h"
#include "AvatarModel.h"
#include "AvatarController.h"
#include "AvatarView.h"
#include "CameraHelpers.h"
#include "SceneModelsModule.h"
#include "TerrainModelModule.h"
#include "AvatarSceneModelFactory.h"
#include "IAnimatedSceneModel.h"
#include "RenderingTransformMeshModule.h"
#include "LocalTexture.h"
#include "LocalTextureFactory.h"
#include "UnlitTexturedMaterialFactory.h"
#include "TexturedVertexMeshFactory.h"
#include "TransformMeshRenderableFactory.h"
#include "TransformMeshRenderableFilter.h"
#include "AvatarLocationChangedObserver.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace AvatarModule
        {
            namespace
            {
                RenderingTransformMesh::SdkModel::TransformMeshRenderable* CreateAvatarShadow(
                                                                                    RenderingTransformMesh::SdkModel::RenderingTransformMeshModule& renderingTransformMeshModule,
                                                                                    const std::string& shadowImageFilename,
                                                                                    Eegeo::Rendering::LayerIds::Values layerId)
                {
                    const bool renderableWillOwnMeshAndMaterial = true;
                    
                    RenderingTransformMesh::SdkModel::LocalTexture& localTexture = renderingTransformMeshModule.GetLocalTextureFactory().CreateTexture(shadowImageFilename);
                    
                    Eegeo::Rendering::Materials::IMaterial* pShadowMaterial;
                    pShadowMaterial = renderingTransformMeshModule.GetUnlitTexturedMaterialFactory().CreateMaterial(localTexture.GetTextureInfo().textureId, "AvatarShadowMaterial");
                    
                    Eegeo::Rendering::Mesh* pShadowMesh;
                    pShadowMesh = renderingTransformMeshModule.GetTexturedVertexMeshFactory().CreateQuadCCWMesh(0.25f, 0.25f, "AvatarShadowMesh");

                    RenderingTransformMesh::SdkModel::TransformMeshRenderableFactory& transformMeshRenderableFactory = renderingTransformMeshModule.GetTransformMeshRenderableFactory();
                    RenderingTransformMesh::SdkModel::TransformMeshRenderable* pAvatarShadowRenderable = transformMeshRenderableFactory.CreateTransformMeshRenderable(pShadowMesh,
                                                                                        pShadowMaterial,
                                                                                        Eegeo::dv3::Zero(),
                                                                                        layerId,
                                                                                        renderableWillOwnMeshAndMaterial);
                    
                    
                    const int userDefinedDrawAfterInteriors = 1;
                    pAvatarShadowRenderable->SetUserDefined(userDefinedDrawAfterInteriors);
                    
                    return pAvatarShadowRenderable;
                }
            }
            
            AvatarModule::AvatarModule(const Eegeo::Modules::Core::SceneModelsModule& sceneModelsModule,
                                                 RenderingTransformMesh::SdkModel::RenderingTransformMeshModule& renderingTransformMeshModule,
                                                 Eegeo::Helpers::IFileIO& fileIO,
                                                 Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule,
                                                 ExampleApp::IndoorLocation::SdkModel::IIndoorLocationDeviceModel& deviceModel,
                                                 Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                 ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                 Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService
                                       )
            {
                m_pSceneModelFactory = Eegeo_NEW(SdkModel::AvatarSceneModelFactory)(sceneModelsModule, fileIO);
                
                
                const std::string idleAnimationFilename = "CharacterIdle_01.POD";
                const std::string walkAnimationFilename = "CharacterWalk_01.POD";
                const std::string shadowImageFilename = "shadow.png";
                const Eegeo::Rendering::LayerIds::Values avatarRenderingLayerId = Eegeo::Rendering::LayerIds::Interiors;
                
                
                SdkModel::IAnimatedSceneModel* pIdleAnimModel = m_pSceneModelFactory->CreateModel(idleAnimationFilename,
                                                                                                  avatarRenderingLayerId);
                
                SdkModel::IAnimatedSceneModel* pWalkAnimModel = m_pSceneModelFactory->CreateModel(walkAnimationFilename,
                                                                                                  avatarRenderingLayerId);
                
                RenderingTransformMesh::SdkModel::TransformMeshRenderable* pAvatarShadow = CreateAvatarShadow(renderingTransformMeshModule,
                                                                                                              shadowImageFilename,
                                                                                                              avatarRenderingLayerId);
                
                m_pAvatarView = Eegeo_NEW(AvatarView)(pIdleAnimModel,
                                                           pWalkAnimModel,
                                                           sceneModelsModule.GetSceneModelRenderableFilter(),
                                                           pAvatarShadow,
                                                           renderingTransformMeshModule.GetTransformMeshRenderableFilter(),
                                                           debugRenderingModule);
                
                m_pAvatarModel = Eegeo_NEW(SdkModel::AvatarModel)();
                m_pAvatarController = Eegeo_NEW(SdkModel::AvatarController)(*m_pAvatarView, *m_pAvatarModel, interiorInteractionModel, environmentFlatteningService, appModeModel);
                m_pLocationChangedObserver = Eegeo_NEW(AvatarLocationChangedObserver)(*m_pAvatarController, deviceModel);

            }
            
            AvatarModule::~AvatarModule()
            {
                Eegeo_DELETE m_pLocationChangedObserver;
                m_pLocationChangedObserver = NULL;

                Eegeo_DELETE m_pAvatarController;
                m_pAvatarController = NULL;
                
                Eegeo_DELETE m_pAvatarModel;
                m_pAvatarModel = NULL;
                
                Eegeo_DELETE m_pAvatarView;
                m_pAvatarView = NULL;
            }
            
            SdkModel::IAvatarView& AvatarModule::GetAvatarView()
            {
                return *m_pAvatarView;
            }
            
            SdkModel::IAvatarController& AvatarModule::GetAvatarController()
            {
                return  *m_pAvatarController;
            }
            
            SdkModel::IAvatarModel& AvatarModule::GetAvatarModel()
            {
                return  *m_pAvatarModel;
            }
            
            void AvatarModule::Update(float dt)
            {
                m_pAvatarController->Update(dt);
                m_pAvatarView->Update(dt);
            }
        }
    }
}