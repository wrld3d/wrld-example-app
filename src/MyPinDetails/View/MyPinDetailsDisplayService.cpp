// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsDisplayService.h"
#include "MyPinModel.h"
#include "ISearchResultPoiViewModel.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsDisplayService::MyPinDetailsDisplayService(const std::shared_ptr<IMyPinDetailsViewModel>& myPinDetailsViewModel,
                                                                   const std::shared_ptr<SearchResultPoi::View::ISearchResultPoiViewModel>& searchResultPoiViewModel,
                                                                   const std::shared_ptr<Menu::View::IMenuReactionModel>& menuReactionModel)
            : m_myPinDetailsViewModel(myPinDetailsViewModel)
            , m_searchResultPoiViewModel(searchResultPoiViewModel)
            , m_menuReaction(menuReactionModel)
            {
                
            }
            
            MyPinDetailsDisplayService::~MyPinDetailsDisplayService()
            
            {
                
            }
            
            
            void MyPinDetailsDisplayService::DisplayUserCreatedMyPinDetails(MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                                                            const std::string& title,
                                                                            const std::string& description,
                                                                            const std::string& imagePath)
            {
                if (!m_myPinDetailsViewModel->IsOpen())
                {
                    m_myPinDetailsViewModel->Open(pinId, title, description, imagePath);
                }
            }
            
            void MyPinDetailsDisplayService::DisplaySearchResultMyPinDetails(const Search::SdkModel::SearchResultModel& searchResultModel)
            {
                if (m_menuReaction->GetShouldOpenMenu())
                {
                    if (!m_searchResultPoiViewModel->IsOpen())
                    {
                        m_searchResultPoiViewModel->Open(searchResultModel, true);
                    }
                }
                else
                {
                    m_searchResultPoiViewModel->Open(searchResultModel, true);
                }
            }
        }
    }
}
