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
#include "CategorySearchMenuOptionFactory.h"

namespace ExampleApp
{
    namespace CategorySearch
    {
        namespace SdkModel
        {
            CategorySearchModule::CategorySearchModule(const std::vector<CategorySearch::View::CategorySearchModel>& categorySearchModels,
                                                       Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                       Menu::View::IMenuViewModel& menuViewModel,
                                                       ExampleAppMessaging::TMessageBus& messageBus,
                                                       Metrics::IMetricsService& metricsService,
                                                       const Menu::View::IMenuReactionModel& menuReaction)
            {
                m_pMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pMenuModel);

                m_pCategorySearchRepository = Eegeo_NEW(View::CategorySearchRepository)(categorySearchModels);

                for(std::vector<View::CategorySearchModel>::const_iterator it = categorySearchModels.begin(); it != categorySearchModels.end(); it++)
                {
                    const View::CategorySearchModel& categorySearchModel = *it;

                    if(categorySearchModel.IsVisibleInSearchMenu())
                    {
                        m_pMenuOptionsModel->AddItem(categorySearchModel.Name(),
                                                     categorySearchModel.Name(),
                                                     "",
                                                     categorySearchModel.Icon(),
                                                     View::CategorySearchMenuOptionFactory::CreateCategorySearchMenuOption(
                                                         categorySearchModel,
                                                         menuViewModel,
                                                         messageBus,
                                                         menuReaction)
                                                     );
                    }
                }


                m_pCategorySearchSelectedMessageHandler = Eegeo_NEW(CategorySearchSelectedMessageHandler)(
                            searchQueryPerformer,
                            messageBus,
                            metricsService
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
