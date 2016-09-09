// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"
#include "Interiors.h"
#include <map>
#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace Combined
        {
            namespace SdkModel
            {
                class CombinedSearchServiceModule : public Search::SdkModel::ISearchServiceModule
                {
                private:
                    Search::SdkModel::ISearchService* m_pSearchService;
                    
                    std::vector<TagSearch::View::TagSearchModel> m_tagSearchModels;
                    
                public:
                    CombinedSearchServiceModule(std::map<std::string, Search::SdkModel::ISearchServiceModule*> searchServiceModules,
                                                Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel);
                    
                    ~CombinedSearchServiceModule();
                    
                    Search::SdkModel::ISearchService& GetSearchService() const;
                };
            }
        }
    }
}