// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationCompositeViewModel.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "IMenuViewModel.h"
#include "ISearchResultMenuViewModel.h"
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
            MyPinCreationCompositeViewModel::MyPinCreationCompositeViewModel(ExampleAppMessaging::TMessageBus& messageBus,
                    IMyPinCreationInitiationViewModel& initiationViewModel,
                    IMyPinCreationConfirmationViewModel& confirmationViewModel,
                    ExampleApp::Menu::View::IMenuViewModel& secondaryMenuViewModel,
                    ExampleApp::Menu::View::IMenuViewModel& searchResultMenuViewModel)
                : m_stateChangeHandler(this, &MyPinCreationCompositeViewModel::OnPoiRingStateChangedMessage)
                , m_searchResultMenuStateChangedCallback(this, &MyPinCreationCompositeViewModel::HandleSearchResultMenuStateChanged)
                , m_messageBus(messageBus)
                , m_initiationViewModel(initiationViewModel)
                , m_confirmationViewModel(confirmationViewModel)
                , m_secondaryMenuViewModel(secondaryMenuViewModel)
                , m_searchResultMenuViewModel(searchResultMenuViewModel)
            {
                m_messageBus.SubscribeUi(m_stateChangeHandler);
                m_searchResultMenuViewModel.InsertOnScreenStateChangedCallback(m_searchResultMenuStateChangedCallback);
            }

            MyPinCreationCompositeViewModel::~MyPinCreationCompositeViewModel()
            {
                m_messageBus.UnsubscribeUi(m_stateChangeHandler);
                m_searchResultMenuViewModel.RemoveOnScreenStateChangedCallback(m_searchResultMenuStateChangedCallback);
            }

            void MyPinCreationCompositeViewModel::OnPoiRingStateChangedMessage(const ExampleApp::MyPinCreation::MyPinCreationStateChangedMessage &message)
            {
                switch (message.GetMyPinCreationStage())
                {
                case Inactive:
                {
                    m_initiationViewModel.AddToScreen();
                    m_secondaryMenuViewModel.AddToScreen();
                    m_searchResultMenuViewModel.AddToScreen();
                    m_messageBus.Publish(WorldPins::WorldPinsVisibilityMessage(WorldPins::SdkModel::WorldPinVisibility::All));
                    m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(true));

                    m_confirmationViewModel.RemoveFromScreen();
                    break;
                }
                case Ring:
                {
                    m_confirmationViewModel.AddToScreen();

                    m_initiationViewModel.RemoveFromScreen();
                    m_secondaryMenuViewModel.RemoveFromScreen();

                    m_messageBus.Publish(WorldPins::WorldPinsVisibilityMessage(WorldPins::SdkModel::WorldPinVisibility::None));
                    m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(false));

                    m_searchResultMenuViewModel.RemoveFromScreen();
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

            void MyPinCreationCompositeViewModel::HandleSearchResultMenuStateChanged(ScreenControl::View::IScreenControlViewModel& viewModel, float& onScreenState)
            {
                if (viewModel.IsFullyOnScreen())
                {
                    m_initiationViewModel.SetShouldOffsetViewButton(true);
                    m_initiationViewModel.AddToScreen();
                }
                else
                {
                    m_initiationViewModel.SetShouldOffsetViewButton(false);
                    if (m_initiationViewModel.IsFullyOnScreen())
                    {
                        m_initiationViewModel.AddToScreen();
                    }
                }
            }
        }
    }
}
