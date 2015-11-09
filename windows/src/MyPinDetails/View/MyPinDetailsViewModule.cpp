// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsViewModule.h"
#include "MyPinDetailsView.h"
#include "MyPinDetailsController.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsViewModule::MyPinDetailsViewModule(
                WindowsNativeState& nativeState,
                IMyPinDetailsViewModel& myPinDetailsViewModel,
                ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pView = Eegeo_NEW(MyPinDetailsView)(nativeState);
                m_pController = Eegeo_NEW(MyPinDetailsController)(*m_pView, myPinDetailsViewModel, messageBus);
            }

            MyPinDetailsViewModule::~MyPinDetailsViewModule()
            {
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }
        }
    }
}
