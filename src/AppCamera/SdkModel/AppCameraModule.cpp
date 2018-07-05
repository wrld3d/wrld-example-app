// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppCameraModule.h"
#include "AppCameraController.h"
#include "AppCameraLocationPicker.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            AppCameraModule::AppCameraModule(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                             Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                             Eegeo::Collision::IFeatureRayCastingService& featureRayCastingService)
            {
                m_pAppCameraController = Eegeo_NEW(AppCameraController)();

                m_pAppCameraLocationPicker = Eegeo_NEW(AppCameraLocationPicker)(*m_pAppCameraController,
                    interiorTransitionModel,
                    interiorInteractionModel,
                    featureRayCastingService);
            }
            
            AppCameraModule::~AppCameraModule()
            {
                Eegeo_DELETE m_pAppCameraLocationPicker;
                m_pAppCameraLocationPicker = NULL;

                Eegeo_DELETE m_pAppCameraController;
                m_pAppCameraController = NULL;
            }
            
            IAppCameraController& AppCameraModule::GetController()
            {
                return *m_pAppCameraController;
            }

            IAppCameraLocationPicker& AppCameraModule::GetLocationPicker()
            {
                return *m_pAppCameraLocationPicker;
            }
            
        }
    }
}
