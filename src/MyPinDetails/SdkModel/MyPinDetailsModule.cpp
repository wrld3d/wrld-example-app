// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsModule.h"
#include "MyPinDetailsViewModel.h"
#include "MyPinDetailsModelSelectedObserver.h"
#include "MyPinDetailsDisplayService.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace SdkModel
        {
            MyPinDetailsModule::MyPinDetailsModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                   Reaction::View::IReactionControllerModel& reactionControllerModel,
                                                   MyPins::SdkModel::IMyPinsService& myPinsService,
                                                   SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel,
                                                   ExampleAppMessaging::TMessageBus& messageBus,
                                                   const Menu::View::IMenuReactionModel& menuReaction)
            {
                m_pMyPinDetailsViewModel = Eegeo_NEW(MyPinDetails::View::MyPinDetailsViewModel)(identityProvider.GetNextIdentity(),
                                           reactionControllerModel);
                
                m_pMyPinDetailsDisplayService = Eegeo_NEW(View::MyPinDetailsDisplayService)(*m_pMyPinDetailsViewModel,
                                                                                            searchResultPoiViewModel,
                                                                                            menuReaction);
                
                m_pMyPinDetailsModelSelectedObserver = Eegeo_NEW(MyPinDetails::View::MyPinDetailsModelSelectedObserver)(*m_pMyPinDetailsDisplayService,
                                                       messageBus);

                m_pMyPinDetailsViewRemovePinHandler = Eegeo_NEW(MyPinDetailsViewRemovePinHandler)(myPinsService,
                                                      messageBus);
            }

            MyPinDetailsModule::~MyPinDetailsModule()
            {
                Eegeo_DELETE m_pMyPinDetailsViewRemovePinHandler;
                Eegeo_DELETE m_pMyPinDetailsModelSelectedObserver;
                Eegeo_DELETE m_pMyPinDetailsDisplayService;
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
