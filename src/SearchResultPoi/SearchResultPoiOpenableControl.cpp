// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultPoiOpenableControl.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        SearchResultPoiOpenableControl::SearchResultPoiOpenableControl(Eegeo::Helpers::TIdentity identity,
                                                                       Reaction::IReactionControllerModel& reactionControllerModel)
        : OpenableControlViewModel::OpenableControlViewModelBase(reactionControllerModel)
        , m_identity(identity)
        {
        }
        
        Eegeo::Helpers::TIdentity SearchResultPoiOpenableControl::GetIdentity() const
        {
            return m_identity;
        }
    }
}
