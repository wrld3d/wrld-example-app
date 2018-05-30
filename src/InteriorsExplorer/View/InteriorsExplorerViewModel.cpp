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
            : m_onScreenState(initiallyOnScreen ? 1.f : 0.f)
            , m_addedToScreen(initiallyOnScreen)
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
                
                m_addedToScreen = true;
                m_onScreenState = 1.f;
                m_onScreenStateChangedCallbacks.ExecuteCallbacks(*this);
            }
            
            void InteriorsExplorerViewModel::RemoveFromScreen()
            {
                m_addedToScreen = false;
                m_onScreenState = 0.f;
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
                return OnScreenState() == 0.f;
            }
            
            bool InteriorsExplorerViewModel::IsOnScreen() const
            {
                return OnScreenState() == 1.f;
            }
            
            float InteriorsExplorerViewModel::OnScreenState() const
            {
                return m_onScreenState;
            }
            
            bool InteriorsExplorerViewModel::IsAddedToScreen() const
            {
                return m_addedToScreen;
            }
            
            void InteriorsExplorerViewModel::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
                m_canAddToScreen = (message.GetAppMode() == AppModes::SdkModel::InteriorMode);
            }
        }
    }
}