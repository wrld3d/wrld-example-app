// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsViewModule.h"
#include "IMyPinDetailsViewModel.h"
#include "MyPinDetailsController.h"
#include "MyPinDetailsView.h"
#include "ScreenProperties.h"
#include "MyPinDetailsViewInterop.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsViewModule::MyPinDetailsViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                    IMyPinDetailsViewModel& viewModel, const Eegeo::Rendering::ScreenProperties& screenProperties)
            {
                m_pView = [[MyPinDetailsView alloc] initWithParams:screenProperties.GetScreenWidth() :screenProperties.GetScreenHeight()];

                m_pController = Eegeo_NEW(MyPinDetailsController)(*[m_pView getInterop], viewModel, messageBus);
            }

            MyPinDetailsViewModule::~MyPinDetailsViewModule()
            {
                Eegeo_DELETE m_pController;

                [m_pView release];
            }

            MyPinDetailsController& MyPinDetailsViewModule::GetMyPinDetailsController() const
            {
                return *m_pController;
            }

            MyPinDetailsView& MyPinDetailsViewModule::GetMyPinDetailsView() const
            {
                return *m_pView;
            }
        }
    }
}
