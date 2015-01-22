// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IIdentity.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class IReactionControllerModel
            {
            public:
                virtual ~IReactionControllerModel() { }

                virtual bool IsAnyOpenableOpen() const = 0;

                virtual bool IsOpenableOpen(Eegeo::Helpers::TIdentity identity) const = 0;

                virtual void AcquireOpenableOpen(Eegeo::Helpers::TIdentity identity) = 0;

                virtual void ReleaseOpenableOpen(Eegeo::Helpers::TIdentity identity) = 0;

                virtual bool IsModalControlAcquired() const = 0;

                virtual bool HasModalControl(Eegeo::Helpers::TIdentity identity) const = 0;

                virtual void AcquireModalControl(Eegeo::Helpers::TIdentity identity) = 0;

                virtual void ReleaseModalControl(Eegeo::Helpers::TIdentity identity) = 0;

                virtual void InsertModalControlAcquiredCallback(Eegeo::Helpers::ICallback0& acquiredCallback) = 0;

                virtual void RemoveModalControlAcquiredCallback(Eegeo::Helpers::ICallback0& acquiredCallback) = 0;

                virtual void InsertModalControlReleasedCallback(Eegeo::Helpers::ICallback0& releasedCallback) = 0;

                virtual void RemoveModalControlReleasedCallback(Eegeo::Helpers::ICallback0& releasedCallback) = 0;

                virtual void InsertOpenControlAcquiredCallback(Eegeo::Helpers::ICallback0& acquiredCallback) = 0;

                virtual void RemoveOpenControlAcquiredCallback(Eegeo::Helpers::ICallback0& acquiredCallback) = 0;

                virtual void InsertOpenControlReleasedCallback(Eegeo::Helpers::ICallback0& releasedCallback) = 0;

                virtual void RemoveOpenControlReleasedCallback(Eegeo::Helpers::ICallback0& releasedCallback) = 0;
            };
        }
    }
}
