// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAvatarSceneModelFactory.h"
#include <string>
#include "IFileIO.h"
#include "Rendering.h"
#include "SceneModelsModule.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            class AvatarSceneModelFactory : public IAvatarSceneModelFactory
            {
            public:
                
                AvatarSceneModelFactory(const Eegeo::Modules::Core::SceneModelsModule& m_sceneModelsModule, Eegeo::Helpers::IFileIO& fileIO);
                
                IAnimatedSceneModel* CreateModel(const std::string& fileName,
                                               const Eegeo::Rendering::LayerIds::Values& renderingLayer);
                
            private:
                const Eegeo::Modules::Core::SceneModelsModule& m_sceneModelsModule;
                Eegeo::Helpers::IFileIO& m_fileIO;
            };
        }
    }
}