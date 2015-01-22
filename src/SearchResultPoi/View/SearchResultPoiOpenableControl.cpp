// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiOpenableControl.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiOpenableControl::SearchResultPoiOpenableControl(Eegeo::Helpers::TIdentity identity,
                    Reaction::View::IReactionControllerModel& reactionControllerModel)
                : OpenableControl::View::OpenableControlViewModelBase(reactionControllerModel)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity SearchResultPoiOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
