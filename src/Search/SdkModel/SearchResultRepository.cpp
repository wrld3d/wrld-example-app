// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultRepository.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchResultRepository::~SearchResultRepository()
            {
                while(GetItemCount() > 0)
                {
                    SearchResultModel* pModel = GetItemAtIndex(0);
                    RemoveItem(pModel);
                    Eegeo_DELETE pModel;
                }
            }

            void SearchResultRepository::RemoveFirstResultWithIdentifier(const std::string& identifier)
            {
                for(size_t i = 0; i < GetItemCount(); ++ i)
                {
                    SearchResultModel& model = *GetItemAtIndex(i);

                    if(model.GetIdentifier() == identifier)
                    {
                        RemoveItem(&model);
                        return;
                    }
                }
            }
        }
    }
}

