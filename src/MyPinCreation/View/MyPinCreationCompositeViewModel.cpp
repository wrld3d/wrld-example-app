// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationCompositeViewModel.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "IMenuViewModel.h"
#include "ISearchQueryPerformer.h"
#include "WorldPinsVisibilityMessage.h"
#include "GpsMarkerVisibilityMessage.h"
#include "WorldPinVisibility.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationCompositeViewModel::MyPinCreationCompositeViewModel(const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                                             const std::shared_ptr<IMyPinCreationInitiationViewModel>& initiationViewModel,
                                                                             const std::shared_ptr<IMyPinCreationConfirmationViewModel>& confirmationViewModel,
                                                                             const std::shared_ptr<SearchMenu::View::SearchMenuViewModel>& searchMenuViewModel,
                                                                             const std::shared_ptr<SettingsMenu::View::SettingsMenuViewModel>& settingsMenuViewModel,
                                                                             const std::shared_ptr<InteriorsExplorer::View::InteriorsExplorerViewModel>& interiorControlViewModel)
                : m_stateChangeHandler(this, &MyPinCreationCompositeViewModel::OnPoiRingStateChangedMessage)
                , m_settingsMenuStateChangedCallback(this, &MyPinCreationCompositeViewModel::HandleSettingsMenuStateChanged)
                , m_messageBus(messageBus)
                , m_initiationViewModel(initiationViewModel)
                , m_confirmationViewModel(confirmationViewModel)
                , m_interiorControlViewModel(interiorControlViewModel)
                , m_searchMenuViewModel(searchMenuViewModel)
                , m_settingsMenuViewModel(settingsMenuViewModel)
            {
                Eegeo_ASSERT(m_messageBus != nullptr);
                Eegeo_ASSERT(m_initiationViewModel != nullptr);
                Eegeo_ASSERT(m_confirmationViewModel != nullptr);
                Eegeo_ASSERT(m_interiorControlViewModel != nullptr);
                Eegeo_ASSERT(m_searchMenuViewModel != nullptr);
                Eegeo_ASSERT(m_settingsMenuViewModel != nullptr);
                
                m_messageBus->SubscribeUi(m_stateChangeHandler);
                m_settingsMenuViewModel->InsertOnScreenStateChangedCallback(m_settingsMenuStateChangedCallback);
            }

            MyPinCreationCompositeViewModel::~MyPinCreationCompositeViewModel()
            {
                m_messageBus->UnsubscribeUi(m_stateChangeHandler);
                m_settingsMenuViewModel->RemoveOnScreenStateChangedCallback(m_settingsMenuStateChangedCallback);
            }

            void MyPinCreationCompositeViewModel::OnPoiRingStateChangedMessage(const ExampleApp::MyPinCreation::MyPinCreationStateChangedMessage &message)
            {
                switch (message.GetMyPinCreationStage())
                {
                case Inactive:
                {
                    m_initiationViewModel->AddToScreen();
                    m_interiorControlViewModel->AddToScreen();
                    m_searchMenuViewModel->AddToScreen();
                    m_settingsMenuViewModel->AddToScreen();

                    m_messageBus->Publish(WorldPins::WorldPinsVisibilityMessage(WorldPins::SdkModel::WorldPinVisibility::All));
                    m_messageBus->Publish(GpsMarker::GpsMarkerVisibilityMessage(true));

                    m_confirmationViewModel->RemoveFromScreen();
                    break;
                }
                case Ring:
                {
                    m_confirmationViewModel->AddToScreen();
                    m_initiationViewModel->RemoveFromScreen();
                    m_interiorControlViewModel->RemoveFromScreen();
                    m_searchMenuViewModel->RemoveFromScreen();

                    m_messageBus->Publish(WorldPins::WorldPinsVisibilityMessage(WorldPins::SdkModel::WorldPinVisibility::None));
                    m_messageBus->Publish(GpsMarker::GpsMarkerVisibilityMessage(false));

                    m_settingsMenuViewModel->RemoveFromScreen();
                    break;
                }
                case Details:
                {
                    break;
                }

                default:
                {
                    Eegeo_ASSERT(false, "Invalid MyPinCreationStage");
                }

                }
            }

            // TODO: Investigate if this is necessary
            void MyPinCreationCompositeViewModel::HandleSettingsMenuStateChanged(ScreenControl::View::IScreenControlViewModel& viewModel, float& onScreenState)
            {
                if (viewModel.IsFullyOnScreen())
                {
                    m_initiationViewModel->SetShouldOffsetViewButton(true);
                    m_initiationViewModel->AddToScreen();
                }
                else
                {
                    m_initiationViewModel->SetShouldOffsetViewButton(false);
                    if (m_initiationViewModel->IsFullyOnScreen())
                    {
                        m_initiationViewModel->AddToScreen();
                    }
                }
            }
        }
    }
}
