// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IAppCameraModule.h"
#include "AppCamera.h"
#include "Interiors.h"
#include "Collision.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class AppCameraModule : public IAppCameraModule
            {
            public:
                
                AppCameraModule(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                Eegeo::Collision::IFeatureRayCastingService& featureRayCastingService);
                ~AppCameraModule();
                
                IAppCameraController& GetController();
                IAppCameraLocationPicker& GetLocationPicker();
                
            private:
                
                IAppCameraController* m_pAppCameraController;
                IAppCameraLocationPicker* m_pAppCameraLocationPicker;
            };
        }
    }
}