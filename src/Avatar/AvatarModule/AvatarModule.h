// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IFileIO.h"
#include "Types.h"
#include "Avatar.h"
#include "IAvatarModule.h"
#include "Modules.h"
#include "Interiors.h"
#include "AppModeModel.h"
#include "Rendering.h"
#include "RenderingTransformMesh.h"
#include "IndoorLocation.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace AvatarModule
        {
            class AvatarModule : public SdkModel::IAvatarModule, Eegeo::NonCopyable
            {
            public:
                
                AvatarModule(const Eegeo::Modules::Core::SceneModelsModule& sceneModelsModule,
                                                     RenderingTransformMesh::SdkModel::RenderingTransformMeshModule& renderingTransformMeshModule,
                                                     Eegeo::Helpers::IFileIO& fileIO,
                                                     Eegeo::Modules::Core::DebugRenderingModule& debugRenderingModule,
                                                     ExampleApp::IndoorLocation::SdkModel::IIndoorLocationDeviceModel& deviceModel,
                                                     Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                     ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                     Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService
                                );
                ~AvatarModule();
                
                SdkModel::IAvatarView& GetAvatarView();
                
                SdkModel::IAvatarController& GetAvatarController();
                
                SdkModel::IAvatarModel& GetAvatarModel();
                
                void Update(float dt);
                
            private:
                SdkModel::IAvatarModel* m_pAvatarModel;
                SdkModel::IAvatarView* m_pAvatarView;
                SdkModel::IAvatarController* m_pAvatarController;
                
                SdkModel::IAvatarSceneModelFactory* m_pSceneModelFactory;
                AvatarLocationChangedObserver* m_pLocationChangedObserver;

            };
        }
    }
}