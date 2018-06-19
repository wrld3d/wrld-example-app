#include "SearchResultsRepository.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchResultsRepository::SearchResultsRepository()
            {

            }

            const int SearchResultsRepository::GetResultOriginalIndexFromCurrentIndex(int index) const
            {
                return m_results[index].GetOriginalIndex();
            }

            const SearchServicesResult::TSdkSearchResult& SearchResultsRepository::GetSdkSearchResultByIndex(int index) const
            {
                return m_results[index].GetSdkSearchResult();
            }

            ISearchProvider::TSearchResults& SearchResultsRepository::GetResults()
            {
                return m_results;
            }

            void SearchResultsRepository::SetResults(const std::vector<TSdkSearchResult>& sdkResults)
            {
                m_results.clear();
                m_results.reserve(sdkResults.size());

                for (std::vector<TSdkSearchResult>::const_iterator it = sdkResults.begin(); it != sdkResults.end(); it++)
                {
                    std::string name = it->GetTitle();
                    std::string desc = it->GetSubtitle();
                    std::string icon = it->GetIconKey();

                    m_results.push_back(SearchServicesResult(name, desc, icon,
                                                                   static_cast<int>(std::distance(sdkResults.begin(), it)),
                                                                   *it));
                }

                std::stable_sort(m_results.begin(), m_results.end());
            }
        }
    }
}