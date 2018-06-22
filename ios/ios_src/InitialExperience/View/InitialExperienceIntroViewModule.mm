// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroViewModule.h"
#include "InitialExperienceIntroView.h"
#include "InitialExperienceIntroBackgroundView.h"
#include "InitialExperienceIntroController.h"
#include "InitialExperienceIntroViewInterop.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            InitialExperienceIntroViewModule::InitialExperienceIntroViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                                                               NavRouting::View::INavWidgetViewModel& navWidgetViewModel,
                                                                               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                               const Eegeo::Rendering::ScreenProperties& screenProperties)
            {
                m_pBackgroundView = [[InitialExperienceIntroBackgroundView alloc] initView];
                m_pView = [[InitialExperienceIntroView alloc] initView: m_pBackgroundView screenProperties:screenProperties];
                
                m_pController = Eegeo_NEW(InitialExperienceIntroController)(*[m_pView getInterop], messageBus, navWidgetViewModel, cameraTransitionController);
            }
            
            InitialExperienceIntroViewModule::~InitialExperienceIntroViewModule()
            {
                Eegeo_DELETE m_pController;
                [m_pView release];
                [m_pBackgroundView release];
            }
        }
    }
}
