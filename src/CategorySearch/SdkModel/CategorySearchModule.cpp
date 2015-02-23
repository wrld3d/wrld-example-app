// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <vector>
#include "CategorySearchModule.h"
#include "CategorySearchModel.h"
#include "CategorySearchMenuOption.h"
#include "CategorySearchRepository.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "CategorySearchSelectedMessageHandler.h"
#include "SearchResultIconCategoryMapper.h"

namespace
{
    std::vector<ExampleApp::CategorySearch::View::CategorySearchModel> GetDeCartaCategories()
    {
        // Some decarta categories from http://developer.decarta.com/Docs/REST/Search#category
        std::vector<ExampleApp::CategorySearch::View::CategorySearchModel> categories;
        categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Coffee", "coffee shop", "coffee"));
        categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Food", "restaurant", "food"));
        categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Nightlife", "night life", "nightlife"));
        categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Arts", "museum", "arts"));
        categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Hotels", "hotel", "hotel"));
        categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Parks", "park", "park"));
        categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Banks", "bank", "bank"));
        return categories;
    }
}

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace SdkModel
        {
            CategorySearchModule::CategorySearchModule(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    Menu::View::IMenuViewModel& menuViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pMenuModel);

                std::vector<View::CategorySearchModel> categories = GetDeCartaCategories();

                m_pCategorySearchRepository = Eegeo_NEW(View::CategorySearchRepository)(categories);

                for(std::vector<View::CategorySearchModel>::iterator it = categories.begin(); it != categories.end(); it++)
                {
                    View::CategorySearchModel& categorySearchModel = *it;

                    m_pMenuOptionsModel->AddItem(categorySearchModel.Name(),
                                                 categorySearchModel.Name(),
                                                 "",
                                                 categorySearchModel.Icon(),
                                                 Eegeo_NEW(View::CategorySearchMenuOption)(categorySearchModel, menuViewModel, messageBus));
                }


                m_pCategorySearchSelectedMessageHandler = Eegeo_NEW(CategorySearchSelectedMessageHandler)(
                            searchQueryPerformer,
                            messageBus
                        );
                
                m_pSearchResultIconCategoryMapper = Eegeo_NEW(SearchResultIconCategoryMapper)();
            }

            CategorySearchModule::~CategorySearchModule()
            {
                Eegeo_DELETE m_pSearchResultIconCategoryMapper;
                Eegeo_DELETE m_pCategorySearchSelectedMessageHandler;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pMenuModel;
                Eegeo_DELETE m_pCategorySearchRepository;
            }

            Menu::View::IMenuModel& CategorySearchModule::GetCategorySearchMenuModel() const
            {
                return *m_pMenuModel;
            }

            View::ICategorySearchRepository& CategorySearchModule::GetCategorySearchRepository() const
            {
                return *m_pCategorySearchRepository;
            }
            
            ISearchResultIconCategoryMapper& CategorySearchModule::GetSearchResultIconCategoryMapper() const
            {
                return *m_pSearchResultIconCategoryMapper;
            }
        }
    }
}
