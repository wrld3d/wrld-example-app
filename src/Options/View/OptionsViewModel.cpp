// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsViewModel.h"

#include <sstream>

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            OptionsViewModel::OptionsViewModel(Eegeo::Helpers::TIdentity identity,
                                               Reaction::View::IReactionControllerModel& reactionControllerModel,
                                               bool streamOverWifiOnly,
                                               bool cachingEnabled)
            : m_openable(identity, reactionControllerModel)
            , m_streamOverWifiOnly(streamOverWifiOnly)
            , m_cachingEnabled(cachingEnabled)
            , m_inCacheClearCeremony(false)
            {
                
            }
            
            OptionsViewModel::~OptionsViewModel()
            {
                
            }
            
            bool OptionsViewModel::StreamOverWifiOnly() const
            {
                return m_streamOverWifiOnly;
            }
            
            bool OptionsViewModel::CachingEnabled() const
            {
                return m_cachingEnabled;
            }
            
            void OptionsViewModel::SetStreamOverWifiOnly(bool value)
            {
                m_streamOverWifiOnly = value;
            }
            
            void OptionsViewModel::SetCachingEnabled(bool value)
            {
                m_cachingEnabled = value;
            }
            
            void OptionsViewModel::BeginCacheClearCeremony()
            {
                Eegeo_ASSERT(!m_inCacheClearCeremony);
                m_inCacheClearCeremony = true;
            }
            
            void OptionsViewModel::EndCacheClearCeremony()
            {
                Eegeo_ASSERT(m_inCacheClearCeremony);
                m_inCacheClearCeremony = false;
                m_cacheClearCeremonyCompletedCallbacks.ExecuteCallbacks();
            }
            
            bool OptionsViewModel::TryAcquireReactorControl()
            {
                return m_openable.TryAcquireReactorControl();
            }
            
            bool OptionsViewModel::IsOpen() const
            {
                return m_openable.IsFullyOpen();
            }
            
            void OptionsViewModel::Open()
            {
                if(!IsOpen())
                {
                    if(m_openable.Open())
                    {
                        m_openedCallbacks.ExecuteCallbacks();
                    }
                }
            }
            
            void OptionsViewModel::Close()
            {
                if(IsOpen())
                {
                    {
                        const bool closed = m_openable.Close();
                        Eegeo_ASSERT(closed, "Failed to close");
                    }
                    
                    m_closedCallbacks.ExecuteCallbacks();
                }
            }
            
            OpenableControl::View::IOpenableControlViewModel& OptionsViewModel::GetOpenableControl()
            {
                return m_openable;
            }
            
            void OptionsViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.AddCallback(openedCallback);
            }
            
            void OptionsViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
            {
                m_openedCallbacks.RemoveCallback(openedCallback);
            }
            
            void OptionsViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.AddCallback(closedCallback);
            }
            
            void OptionsViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
            {
                m_closedCallbacks.RemoveCallback(closedCallback);
            }
            
            void OptionsViewModel::InsertCacheClearCeremonyCompletedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_cacheClearCeremonyCompletedCallbacks.AddCallback(callback);
            }
            
            void OptionsViewModel::RemoveCacheClearCeremonyCompletedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_cacheClearCeremonyCompletedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
