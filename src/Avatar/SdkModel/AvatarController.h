// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAvatarController.h"

#include "Interiors.h"
#include "Location.h"
#include "AppModeModel.h"
#include "Avatar.h"
#include "ICallback.h"
#include "EnvironmentFlatteningService.h"

namespace ExampleApp
{
    namespace Avatar
    {
        namespace SdkModel
        {
            class AvatarController : public IAvatarController
            {
            public:
                
                AvatarController(IAvatarView& avatarView,
                                 IAvatarModel& avatarModel,
                                 Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                 Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                 ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel);
                
                ~AvatarController();
                
                void SetModelTarget(const Eegeo::Space::LatLong& latLong, const Eegeo::Resources::Interiors::InteriorId& building, int floor);
                
                void Update(float dt);
                
            private:
                
                void OnAppModeChanged();
                
                bool ShouldShowAvatar();
                
                void UpdateAvatarVisibility();
                
                IAvatarView& m_avatarView;
                IAvatarModel& m_avatarModel;
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
                Eegeo::Helpers::TCallback0<AvatarController> m_appModeChangedCallback;
                Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
            };
        }
    }
}