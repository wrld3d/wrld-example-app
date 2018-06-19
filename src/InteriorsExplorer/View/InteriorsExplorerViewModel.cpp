// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerViewModel.h"
#include "AppModeModel.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            InteriorsExplorerViewModel::InteriorsExplorerViewModel(bool initiallyOnScreen,
                                                                   Eegeo::Helpers::TIdentity identity,
                                                                   ExampleAppMessaging::TMessageBus& messageBus)
            : m_isOnScreen(initiallyOnScreen)
            , m_viewState(DisplayMode::Default)
            , m_identity(identity)
            , m_messageBus(messageBus)
            , m_canAddToScreen(false)
            , m_appModeChangedCallback(this, &InteriorsExplorerViewModel::OnAppModeChanged)
            {
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
            }
            
            InteriorsExplorerViewModel::~InteriorsExplorerViewModel()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
            }
            
            Eegeo::Helpers::TIdentity InteriorsExplorerViewModel::GetIdentity() const
            {
                return m_identity;
            }
            
            void InteriorsExplorerViewModel::AddToScreen()
            {
                if(!m_canAddToScreen)
                {
                    return;
                }

                m_isOnScreen = true;
                m_onScreenStateChangedCallbacks.ExecuteCallbacks(*this);
            }
            
            void InteriorsExplorerViewModel::RemoveFromScreen()
            {
                if(IsOffScreen()){
                    return;
                }
                m_isOnScreen = false;
                m_onScreenStateChangedCallbacks.ExecuteCallbacks(*this);
            }

            void InteriorsExplorerViewModel::InsertOnScreenStateChangedCallback(
                    Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback)
            {
                m_onScreenStateChangedCallbacks.AddCallback(callback);
            }
            
            void InteriorsExplorerViewModel::RemoveOnScreenStateChangedCallback(
                    Eegeo::Helpers::ICallback1<IScreenControlViewModel &> &callback)
            {
                m_onScreenStateChangedCallbacks.RemoveCallback(callback);
            }
            
            bool InteriorsExplorerViewModel::IsOffScreen() const
            {
                return !m_isOnScreen;
            }
            
            bool InteriorsExplorerViewModel::IsOnScreen() const
            {
                return m_isOnScreen;
            }

            void InteriorsExplorerViewModel::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
                m_canAddToScreen = (message.GetAppMode() == AppModes::SdkModel::InteriorMode);
            }

            ScreenControl::View::IMultiStateScreenControlViewModel& InteriorsExplorerViewModel::GetScreenControlViewModel()
            {
                return *this;
            }

            void InteriorsExplorerViewModel::SetState(
                    ScreenControl::View::TScreenControlViewState screenControlViewState)
            {
                m_viewState = screenControlViewState;
                if(m_isOnScreen)
                {
                    m_onScreenStateChangedCallbacks.ExecuteCallbacks(*this);
                }
            }

            ScreenControl::View::TScreenControlViewState InteriorsExplorerViewModel::GetState()
            {
                return m_viewState;
            }
        }
    }
}