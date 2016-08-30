// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsOpenableControl.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            OptionsOpenableControl::OptionsOpenableControl(Eegeo::Helpers::TIdentity identity, const std::shared_ptr<Reaction::View::IReactionControllerModel>& reactionControllerModel)
                : OpenableControl::View::OpenableControlViewModelBase(reactionControllerModel)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity OptionsOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
