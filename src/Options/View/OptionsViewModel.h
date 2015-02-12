// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IOptionsViewModel.h"
#include "CallbackCollection.h"
#include "OptionsOpenableControl.h"
#include "Reaction.h"
#include "Options.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            class OptionsViewModel : public IOptionsViewModel, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_cacheClearCeremonyCompletedCallbacks;
                OptionsOpenableControl m_openable;
                bool m_streamOverWifiOnly;
                bool m_cachingEnabled;
                bool m_inCacheClearCeremony;
                
            public:
                OptionsViewModel(Eegeo::Helpers::TIdentity identity,
                                 Reaction::View::IReactionControllerModel& reactionControllerModel,
                                 bool streamOverWifiOnly,
                                 bool cachingEnabled);
                
                ~OptionsViewModel();
                
                bool StreamOverWifiOnly() const;
                
                bool CachingEnabled() const;
                
                void SetStreamOverWifiOnly(bool value);
                
                void SetCachingEnabled(bool value);
                
                void BeginCacheClearCeremony();
                
                void EndCacheClearCeremony();
                
                bool TryAcquireReactorControl();
                
                bool IsOpen() const;

                void Open();

                void Close();

                OpenableControl::View::IOpenableControlViewModel& GetOpenableControl();

                void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);

                void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);

                void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);

                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
                
                void InsertCacheClearCeremonyCompletedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void RemoveCacheClearCeremonyCompletedCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
