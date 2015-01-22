// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "SearchResultPoi.h"
#include "ISearchResultPoiModule.h"
#include "SearchResultPoiViewModel.h"
#include "IIdentity.h"
#include "Reaction.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class SearchResultPoiModule: public ISearchResultPoiModule, private Eegeo::NonCopyable
            {
            private:
                SearchResultPoiViewModel* m_pSearchResultPoiViewModel;

            public:
                SearchResultPoiModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                      Reaction::View::IReactionControllerModel& reactionControllerModel);

                ~SearchResultPoiModule();

                ISearchResultPoiViewModel& GetSearchResultPoiViewModel() const;

                OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const;
            };
        }
    }
}
