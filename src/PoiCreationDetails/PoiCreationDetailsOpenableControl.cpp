// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationDetailsOpenableControl.h"

namespace ExampleApp
{
    namespace PoiCreationDetails
    {
        PoiCreationDetailsOpenableControl::PoiCreationDetailsOpenableControl(Eegeo::Helpers::TIdentity identity, Reaction::IReactionControllerModel& reactionControllerModel)
        : OpenableControlViewModel::OpenableControlViewModelBase(reactionControllerModel)
        , m_identity(identity)
        {
        }
        
        Eegeo::Helpers::TIdentity PoiCreationDetailsOpenableControl::GetIdentity() const
        {
            return m_identity;
        }
    }
}
