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
            class CategorySearchMenuModel : public Menu::View::MenuModel
            {
            };
            
            class CategorySearchMenuOptionsModel : public Menu::View::MenuOptionsModel
            {
            public:
                CategorySearchMenuOptionsModel(const std::shared_ptr<CategorySearchMenuModel>& categorySearch) : Menu::View::MenuOptionsModel(*categorySearch)
                {
                }
            };
            
            void CategorySearchModule::Register(const TContainerBuilder& builder)
            {
                builder->registerType<View::TCategories>().singleInstance();
                builder->registerType<View::CategorySearchRepository>().as<View::ICategorySearchRepository>().singleInstance();
                builder->registerType<CategorySearchMenuModel>().singleInstance();
                builder->registerType<CategorySearchMenuOptionsModel>().singleInstance();
                builder->registerType<CategorySearchSelectedMessageHandler>().singleInstance();
            }
            
            void CategorySearchModule::RegisterLeaves()
            {
                RegisterLeaf<CategorySearchSelectedMessageHandler>();
            }
            
            /*
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
            }*/
        }
    }
}
