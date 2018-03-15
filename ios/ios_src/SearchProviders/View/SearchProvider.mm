// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchProvider.h"

namespace ExampleApp
{
    namespace SearchProviders
    {
        SearchProvider::SearchProvider()
        {
        }

        SearchProvider::~SearchProvider()
        {
        }

        void SearchProvider::OnSearchResponseReceived(const TSearchResults& searchResults)
        {
        }

        void SearchProvider::InsertSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
        {
            m_searchPerformedCallbacks.AddCallback(callback);
        }

        void SearchProvider::RemoveSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
        {
            m_searchPerformedCallbacks.RemoveCallback(callback);
        }

        void SearchProvider::InsertSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&, const SearchMenu::View::QueryContext&>& callback)
        {
            m_searchWithContextCallbacks.AddCallback(callback);
        }

        void SearchProvider::RemoveSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&, const SearchMenu::View::QueryContext&>& callback)
        {
            m_searchWithContextCallbacks.RemoveCallback(callback);
        }

        void SearchProvider::InsertSearchRefreshedCallback(Eegeo::Helpers::ICallback2<const std::string&,
                                                                                            const SearchMenu::View::QueryContext&>& callback)
        {
            // Might not be required
        }

        void SearchProvider::RemoveSearchRefreshedCallback(Eegeo::Helpers::ICallback2<const std::string&,
                                                                                            const SearchMenu::View::QueryContext&>& callback)
        {
            // Might not be required
        }

        void SearchProvider::InsertSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback)
        {
            m_searchCancelledCallbacks.AddCallback(callback);
        }

        void SearchProvider::RemoveSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback)
        {
            m_searchCancelledCallbacks.RemoveCallback(callback);
        }
    }
}
