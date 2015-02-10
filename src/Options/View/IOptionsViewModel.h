// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"

#include <string>

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            class IOptionsViewModel
            {
            public:
                virtual ~IOptionsViewModel() { }
                
                virtual bool StreamOverWifiOnly() const = 0;
                
                virtual bool CachingEnabled() const = 0;
                
                virtual void SetStreamOverWifiOnly(bool value) = 0;
                
                virtual void SetCachingEnabled(bool value) = 0;
                
                virtual void BeginCacheClearCeremony() = 0;
                
                virtual void EndCacheClearCeremony() = 0;

                virtual bool TryAcquireReactorControl() = 0;

                virtual bool IsOpen() const = 0;

                virtual void Open() = 0;

                virtual void Close() = 0;

                virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
                
                virtual void InsertCacheClearCeremonyCompletedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void RemoveCacheClearCeremonyCompletedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
