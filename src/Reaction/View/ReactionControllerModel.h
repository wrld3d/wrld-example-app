// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IReactionControllerModel.h"
#include "Types.h"
#include "CallbackCollection.h"
#include "IMenuIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class ReactionControllerModel : public IReactionControllerModel, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::TIdentity m_currentExpandedOpenableIdentity;
                Eegeo::Helpers::TIdentity m_reactorControlIdentity;
                
                const Menu::View::IMenuIgnoredReactionModel& m_menuIgnoredReaction;
                
                Eegeo::Helpers::CallbackCollection0 m_reactorAcquiredCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_reactorReleasedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_openAcquiredCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_openReleasedCallbacks;

            public:
                ReactionControllerModel(const Menu::View::IMenuIgnoredReactionModel& menuIgnoredReaction);

                bool IsAnyOpenableOpen() const;

                bool IsOpenableOpen(Eegeo::Helpers::TIdentity identity) const;

                void AcquireOpenableOpen(Eegeo::Helpers::TIdentity identity);

                void ReleaseOpenableOpen(Eegeo::Helpers::TIdentity identity);

                bool IsModalControlAcquired() const;

                bool HasModalControl(Eegeo::Helpers::TIdentity identity) const;

                void AcquireModalControl(Eegeo::Helpers::TIdentity identity);

                void ReleaseModalControl(Eegeo::Helpers::TIdentity identity);

                void InsertModalControlAcquiredCallback(Eegeo::Helpers::ICallback0& acquiredCallback);

                void RemoveModalControlAcquiredCallback(Eegeo::Helpers::ICallback0& acquiredCallback);

                void InsertModalControlReleasedCallback(Eegeo::Helpers::ICallback0& releasedCallback);

                void RemoveModalControlReleasedCallback(Eegeo::Helpers::ICallback0& releasedCallback);

                void InsertOpenControlAcquiredCallback(Eegeo::Helpers::ICallback0& acquiredCallback);

                void RemoveOpenControlAcquiredCallback(Eegeo::Helpers::ICallback0& acquiredCallback);

                void InsertOpenControlReleasedCallback(Eegeo::Helpers::ICallback0& releasedCallback);

                void RemoveOpenControlReleasedCallback(Eegeo::Helpers::ICallback0& releasedCallback);
            };
        }
    }
}
