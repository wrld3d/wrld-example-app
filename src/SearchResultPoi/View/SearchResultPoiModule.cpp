// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiModule.h"
#include "SearchResultPoiViewModel.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiModule::SearchResultPoiModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                    Reaction::View::IReactionControllerModel& reactionControllerModel)
            {
                m_pSearchResultPoiViewModel = Eegeo_NEW(SearchResultPoiViewModel)(identityProvider.GetNextIdentity(),
                                              reactionControllerModel);
            }

            SearchResultPoiModule::~SearchResultPoiModule()
            {
                Eegeo_DELETE m_pSearchResultPoiViewModel;
            }

            ISearchResultPoiViewModel& SearchResultPoiModule::GetSearchResultPoiViewModel() const
            {
                return *m_pSearchResultPoiViewModel;
            }

            OpenableControl::View::IOpenableControlViewModel& SearchResultPoiModule::GetObservableOpenableControl() const
            {
                return m_pSearchResultPoiViewModel->GetOpenableControl();
            }
        }
    }
}
