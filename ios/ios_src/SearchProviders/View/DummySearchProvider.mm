// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "DummySearchProvider.h"

namespace ExampleApp
{
    namespace SearchProviders
    {
        DummySearchProvider::DummySearchProvider()
        {
        }
        
        DummySearchProvider::~DummySearchProvider()
        {
        }
        
        void DummySearchProvider::OnSearchResponseReceived(const TSearchResults& searchResults)
        {
        }
        
        void DummySearchProvider::InsertSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
        {
        }
        
        void DummySearchProvider::RemoveSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
        {
        }
        
        void DummySearchProvider::InsertSearchRefreshedCallback(Eegeo::Helpers::ICallback2<const std::string&,
                                                                                            const SearchMenu::View::QueryContext&>& callback)
        {
        }
        
        void DummySearchProvider::RemoveSearchRefreshedCallback(Eegeo::Helpers::ICallback2<const std::string&,
                                                                                            const SearchMenu::View::QueryContext&>& callback)
        {
        }
        
        void DummySearchProvider::InsertSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback)
        {
        }
        
        void DummySearchProvider::RemoveSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback)
        {
        }
    }
}
