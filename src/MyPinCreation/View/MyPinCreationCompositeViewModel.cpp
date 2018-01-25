// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationCompositeViewModel.h"
#include "IMyPinCreationInitiationViewModel.h"
#include "IMyPinCreationConfirmationViewModel.h"
#include "IMenuViewModel.h"
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
                    ExampleApp::Menu::View::IMenuViewModel& menuViewModel,
                    ScreenControl::View::IScreenControlViewModel& interiorControlViewModel)
                : m_stateChangeHandler(this, &MyPinCreationCompositeViewModel::OnPoiRingStateChangedMessage)
                , m_menuStateChangedCallback(this, &MyPinCreationCompositeViewModel::HandleSettingsMenuStateChanged)
                , m_messageBus(messageBus)
                , m_initiationViewModel(initiationViewModel)
                , m_confirmationViewModel(confirmationViewModel)
                , m_interiorControlViewModel(interiorControlViewModel)
                , m_menuViewModel(menuViewModel)
                , m_showUiComponents(true)
                , m_appModeChangedCallback(this, &MyPinCreationCompositeViewModel::OnAppModeChanged)
            {
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
                m_messageBus.SubscribeUi(m_stateChangeHandler);
                m_menuViewModel.InsertOnScreenStateChangedCallback(m_menuStateChangedCallback);
            }

            MyPinCreationCompositeViewModel::~MyPinCreationCompositeViewModel()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
                m_messageBus.UnsubscribeUi(m_stateChangeHandler);
                m_menuViewModel.RemoveOnScreenStateChangedCallback(m_menuStateChangedCallback);
            }

            void MyPinCreationCompositeViewModel::OnPoiRingStateChangedMessage(const ExampleApp::MyPinCreation::MyPinCreationStateChangedMessage &message)
            {
                switch (message.GetMyPinCreationStage())
                {
                case Inactive:
                {
                    if (m_showUiComponents)
                    {
                        m_initiationViewModel.AddToScreen();
                        m_interiorControlViewModel.AddToScreen();
                        m_menuViewModel.AddToScreen();

                        m_messageBus.Publish(WorldPins::WorldPinsVisibilityMessage(WorldPins::SdkModel::WorldPinVisibility::All));
                        m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(true));
                    }

                    m_confirmationViewModel.RemoveFromScreen();
                    m_confirmationViewModel.TryReleaseReactorControl();
                    break;
                }
                case Ring:
                {
                    m_confirmationViewModel.AddToScreen();
                    m_initiationViewModel.RemoveFromScreen();
                    m_interiorControlViewModel.RemoveFromScreen();
                    m_menuViewModel.RemoveFromScreen();

                    m_messageBus.Publish(WorldPins::WorldPinsVisibilityMessage(WorldPins::SdkModel::WorldPinVisibility::None));
                    m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(false));
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

            void MyPinCreationCompositeViewModel::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
                m_showUiComponents = message.GetAppMode() != AppModes::SdkModel::AttractMode;
            }
        }
    }
}
