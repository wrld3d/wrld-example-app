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
                m_onScreenStateChangedCallbacks.ExecuteCallbacks(*this, m_onScreenState);
            }
            
            void InteriorsExplorerViewModel::RemoveFromScreen()
            {
                m_addedToScreen = false;
                m_onScreenState = 0.f;
                m_onScreenStateChangedCallbacks.ExecuteCallbacks(*this, m_onScreenState);
            }
            
            void InteriorsExplorerViewModel::UpdateOnScreenState(float onScreenState)
            {
                if(!m_canAddToScreen)
                {
                    m_onScreenState = 0.0f;
                    return;
                }
                
                if(m_addedToScreen)
                {
                    Eegeo_ASSERT(onScreenState >= 0.f && onScreenState <= 1.f, "Invalid value %f for screen state, valid range for UI on-screen-state is 0.0 to 1.0 inclusive.\n", onScreenState);
                    m_onScreenState = onScreenState;
                    m_onScreenStateChangedCallbacks.ExecuteCallbacks(*this, m_onScreenState);
                }
            }
            
            void InteriorsExplorerViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<IScreenControlViewModel&, float>& callback)
            {
                m_onScreenStateChangedCallbacks.AddCallback(callback);
            }
            
            void InteriorsExplorerViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<IScreenControlViewModel&, float>& callback)
            {
                m_onScreenStateChangedCallbacks.RemoveCallback(callback);
            }
            
            bool InteriorsExplorerViewModel::IsFullyOffScreen() const
            {
                return OnScreenState() == 0.f;
            }
            
            bool InteriorsExplorerViewModel::IsFullyOnScreen() const
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