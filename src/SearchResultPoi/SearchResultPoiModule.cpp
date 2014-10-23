// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultPoiModule.h"
#include "SearchResultPoiViewModel.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        SearchResultPoiModule::SearchResultPoiModule(Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                     Reaction::IReactionControllerModel& reactionControllerModel)
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
        
        OpenableControlViewModel::IOpenableControlViewModel& SearchResultPoiModule::GetObservableOpenableControl() const
        {
            return m_pSearchResultPoiViewModel->GetOpenableControl();
        }
    }
}
