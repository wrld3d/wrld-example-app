// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationCompositeViewModel.h"
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
                    IMyPinCreationConfirmationViewModel& confirmationViewModel,
                    ExampleApp::Menu::View::IMenuViewModel& menuViewModel,
                    ScreenControl::View::IScreenControlViewModel& interiorControlViewModel)
                : m_stateChangeHandler(this, &MyPinCreationCompositeViewModel::OnPoiRingStateChangedMessage)
                , m_messageBus(messageBus)
                , m_confirmationViewModel(confirmationViewModel)
                , m_interiorControlViewModel(interiorControlViewModel)
                , m_menuViewModel(menuViewModel)
                , m_showUiComponents(true)
                , m_appModeChangedCallback(this, &MyPinCreationCompositeViewModel::OnAppModeChanged)
            {
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
                m_messageBus.SubscribeUi(m_stateChangeHandler);
            }

            MyPinCreationCompositeViewModel::~MyPinCreationCompositeViewModel()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
                m_messageBus.UnsubscribeUi(m_stateChangeHandler);
            }

            void MyPinCreationCompositeViewModel::OnPoiRingStateChangedMessage(const ExampleApp::MyPinCreation::MyPinCreationStateChangedMessage &message)
            {
                switch (message.GetMyPinCreationStage())
                {
                case Inactive:
                {
                    if (m_showUiComponents)
                    {
                        m_interiorControlViewModel.AddToScreen();
                        m_menuViewModel.AddToScreen();

                        m_messageBus.Publish(WorldPins::WorldPinsVisibilityMessage(true));
                        m_messageBus.Publish(GpsMarker::GpsMarkerVisibilityMessage(true));
                    }

                    m_confirmationViewModel.RemoveFromScreen();
                    m_confirmationViewModel.TryReleaseReactorControl();
                    break;
                }
                case Ring:
                {
                    m_confirmationViewModel.AddToScreen();
                    m_interiorControlViewModel.RemoveFromScreen();
                    m_menuViewModel.RemoveFromScreen();

                    m_messageBus.Publish(WorldPins::WorldPinsVisibilityMessage(false));
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

            void MyPinCreationCompositeViewModel::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
                m_showUiComponents = message.GetAppMode() != AppModes::SdkModel::AttractMode;
            }
        }
    }
}
