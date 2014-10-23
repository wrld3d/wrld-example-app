// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapFactory.h"
#include "ISearchResultPoiViewModel.h"
#include "SearchResultOnMapItemModel.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        SearchResultOnMapFactory::SearchResultOnMapFactory(SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel)
        : m_searchResultPoiViewModel(searchResultPoiViewModel)
        {
            
        }
        
        SearchResultOnMapFactory::~SearchResultOnMapFactory()
        {
            
        }
        
        SearchResultOnMapItemModel* SearchResultOnMapFactory::CreateSearchResultOnMapItemModel(Search::SearchResultModel& searchResultModel) const
        {
            return Eegeo_NEW(SearchResultOnMapItemModel(searchResultModel,
                                                        m_searchResultPoiViewModel));
        }
    }
}
