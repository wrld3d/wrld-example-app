// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsModule.h"
#include "MyPinDetailsViewModel.h"
#include "MyPinDetailsModelSelectedObserver.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace SdkModel
        {
            MyPinDetailsModule::MyPinDetailsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                   Reaction::View::IReactionControllerModel& reactionControllerModel,
                                                   MyPins::SdkModel::IMyPinsService& myPinsService,
                                                   ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pMyPinDetailsViewModel = Eegeo_NEW(MyPinDetails::View::MyPinDetailsViewModel)(identityProvider.GetNextIdentity(),
                                           reactionControllerModel);

                m_pMyPinDetailsModelSelectedObserver = Eegeo_NEW(MyPinDetails::View::MyPinDetailsModelSelectedObserver)(*m_pMyPinDetailsViewModel,
                                                       messageBus);

                m_pMyPinDetailsViewRemovePinHandler = Eegeo_NEW(MyPinDetailsViewRemovePinHandler)(myPinsService,
                                                      messageBus);
            }

            MyPinDetailsModule::~MyPinDetailsModule()
            {
                Eegeo_DELETE m_pMyPinDetailsModelSelectedObserver;
                Eegeo_DELETE m_pMyPinDetailsViewModel;
            }

            MyPinDetails::View::IMyPinDetailsViewModel& MyPinDetailsModule::GetMyPinDetailsViewModel() const
            {
                return *m_pMyPinDetailsViewModel;
            }

            OpenableControl::View::IOpenableControlViewModel& MyPinDetailsModule::GetObservableOpenableControl() const
            {
                return m_pMyPinDetailsViewModel->GetOpenableControl();
            }
        }
    }
}
