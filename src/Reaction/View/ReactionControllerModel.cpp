// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ReactionControllerModel.h"
#include "Types.h"
#include "Logger.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace
        {
            Eegeo::Helpers::TIdentity Unacquired = -1;
        }

        namespace View
        {
            ReactionControllerModel::ReactionControllerModel(const Menu::View::IMenuIgnoredReactionModel& menuIgnoredReaction)
                : m_currentExpandedOpenableIdentity(Unacquired)
                , m_reactorControlIdentity(Unacquired)
                , m_menuIgnoredReaction(menuIgnoredReaction)
            {

            }

            bool ReactionControllerModel::IsAnyOpenableOpen() const
            {
                return m_currentExpandedOpenableIdentity != Unacquired;
            }

            bool ReactionControllerModel::IsOpenableOpen(Eegeo::Helpers::TIdentity identity) const
            {
                return m_currentExpandedOpenableIdentity == identity;
            }

            void ReactionControllerModel::AcquireOpenableOpen(Eegeo::Helpers::TIdentity identity)
            {
                if (m_menuIgnoredReaction.IsIgnored(identity))
                {
                    return;
                }

                Eegeo_ASSERT(!IsAnyOpenableOpen());
                m_currentExpandedOpenableIdentity = identity;
                m_openAcquiredCallbacks.ExecuteCallbacks();
            }

            void ReactionControllerModel::ReleaseOpenableOpen(Eegeo::Helpers::TIdentity identity)
            {
                if (m_menuIgnoredReaction.IsIgnored(identity))
                {
                    return;
                }

                Eegeo_ASSERT(IsOpenableOpen(identity));
                m_currentExpandedOpenableIdentity = Unacquired;
                m_openReleasedCallbacks.ExecuteCallbacks();
            }

            bool ReactionControllerModel::IsModalControlAcquired() const
            {
                return m_reactorControlIdentity != Unacquired;
            }

            bool ReactionControllerModel::HasModalControl(Eegeo::Helpers::TIdentity identity) const
            {
                return m_reactorControlIdentity == identity;
            }

            void ReactionControllerModel::AcquireModalControl(Eegeo::Helpers::TIdentity identity)
            {
                Eegeo_ASSERT(!IsModalControlAcquired());
                m_reactorControlIdentity = identity;
                m_reactorAcquiredCallbacks.ExecuteCallbacks();
                //EXAMPLE_LOG("AcquireModalControl --> %d\n", m_controllerIdentity);
            }

            void ReactionControllerModel::ReleaseModalControl(Eegeo::Helpers::TIdentity identity)
            {
                Eegeo_ASSERT(HasModalControl(identity));
                //EXAMPLE_LOG("ReleaseModalControl --> %d\n", identity);
                m_reactorControlIdentity = Unacquired;
                m_reactorReleasedCallbacks.ExecuteCallbacks();
            }

            void ReactionControllerModel::InsertModalControlAcquiredCallback(Eegeo::Helpers::ICallback0& acquiredCallback)
            {
                m_reactorAcquiredCallbacks.AddCallback(acquiredCallback);
            }

            void ReactionControllerModel::RemoveModalControlAcquiredCallback(Eegeo::Helpers::ICallback0& acquiredCallback)
            {
                m_reactorAcquiredCallbacks.RemoveCallback(acquiredCallback);
            }

            void ReactionControllerModel::InsertModalControlReleasedCallback(Eegeo::Helpers::ICallback0& releasedCallback)
            {
                m_reactorReleasedCallbacks.AddCallback(releasedCallback);
            }

            void ReactionControllerModel::RemoveModalControlReleasedCallback(Eegeo::Helpers::ICallback0& releasedCallback)
            {
                m_reactorReleasedCallbacks.RemoveCallback(releasedCallback);
            }

            void ReactionControllerModel::InsertOpenControlAcquiredCallback(Eegeo::Helpers::ICallback0& acquiredCallback)
            {
                m_openAcquiredCallbacks.AddCallback(acquiredCallback);
            }

            void ReactionControllerModel::RemoveOpenControlAcquiredCallback(Eegeo::Helpers::ICallback0& acquiredCallback)
            {
                m_openAcquiredCallbacks.RemoveCallback(acquiredCallback);
            }

            void ReactionControllerModel::InsertOpenControlReleasedCallback(Eegeo::Helpers::ICallback0& releasedCallback)
            {
                m_openReleasedCallbacks.AddCallback(releasedCallback);
            }

            void ReactionControllerModel::RemoveOpenControlReleasedCallback(Eegeo::Helpers::ICallback0& releasedCallback)
            {
                m_openReleasedCallbacks.RemoveCallback(releasedCallback);
            }
        }
    }
}
