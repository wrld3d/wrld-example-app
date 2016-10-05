// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TagSearchModule.h"
#include "TagSearchMenuOption.h"
#include "TagSearchMenuOptionFactory.h"
#include "TagSearchRepository.h"
#include "TagSearchRepositoryObserver.h"
#include "TagSearchSelectedMessageHandler.h"
#include "SearchResultIconKeyMapper.h"
#include "TagSearchModelFactory.h"
#include "IFileIO.h"
#include "TagSearchSectionController.h"
#include "EegeoTagIconMapper.h"
#include "ITagIconMapper.h"
#include "SearchTags.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            void TagSearchModule::Register(const TContainerBuilder &builder)
            {
                builder->registerType<View::TagSearchMenuModel>().singleInstance();
                builder->registerType<View::TagSearchMenuOptionsModel>().singleInstance();
                builder->registerType<View::TagSearchRepository>().as<View::ITagSearchRepository>().singleInstance();
                builder->registerType<TagSearchRepositoryObserver>().singleInstance();
                builder->registerType<SearchResultIconKeyMapper>().as<ISearchResultIconKeyMapper>().singleInstance();
                builder->registerType<View::TagSearchSectionController>().singleInstance();
                builder->registerType<EegeoTagIconMapper>().as<ITagIconMapper>().singleInstance();
            }
            
            void TagSearchModule::RegisterNativeLeaves()
            {
                RegisterLeaf<TagSearchRepositoryObserver>();
                RegisterLeaf<TagSearchSelectedMessageHandler>();
                
                const auto& tagSearchModels = TagSearch::View::CreateTagSearchModelsFromFile(
                                                                                             *Resolve<Eegeo::Helpers::IFileIO>(),
                                                                                             "search_menu_items.json");
                
                const auto& repository = Resolve<View::ITagSearchRepository>();
                for (const auto& t : tagSearchModels)
                {
                    repository->AddItem(t);
                }
            }
            
            void TagSearchModule::RegisterUiLeaves()
            {
                RegisterLeaf<View::TagSearchSectionController>();
            }
        }
    }
}
