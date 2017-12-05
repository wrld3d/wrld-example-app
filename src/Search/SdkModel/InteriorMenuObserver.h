// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorSelectionModel.h"
#include "InteriorMetaDataRepository.h"
#include "TagSearchRepository.h"
#include "YelpCategoryMapperUpdater.h"
#include "IModelRepository.h"
#include "ApplicationMenuItemTagSearchConfig.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class InteriorMenuObserver : private Eegeo::NonCopyable, public Eegeo::Resources::Interiors::MetaData::IInteriorMetaDataRepository::ObserverType
            {
            public:
                InteriorMenuObserver(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                     Eegeo::Resources::Interiors::MetaData::IInteriorMetaDataRepository& interiorMetaDataRepo,
                                     TagSearch::View::ITagSearchRepository& tagSearchRepository,
                                     Search::Yelp::SdkModel::YelpCategoryMapperUpdater& yelpCategoryMapperUpdater,
                                     std::vector<TagSearch::View::TagSearchModel> defaultFindMenuEntries,
                                     Search::SdkModel::TagIconKey defaultIconKey);
                ~InteriorMenuObserver();
                TagSearch::View::ITagSearchRepository& GetTagsRepository() { return m_tagSearchRepository; }
                void RegisterInteriorTagsUpdatedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void UnregisterInteriorTagsUpdatedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void UpdateDefaultOutdoorSearchMenuItems(const std::vector<ExampleApp::ApplicationConfig::SdkModel::ApplicationMenuItemTagSearchConfig>& menuItems,
                                                         bool overrideIndoorSearchMenuItems);
                
                void ApplyCustomInteriorSearchMenuItems(const Eegeo::Resources::Interiors::InteriorId& interiorId);
                
            private:
                enum TransitionState
                {
                    EnteringBuilding = 0,
                    LeavingBuilding,
                    SwitchingBuilding,
                    NoTransition
                };

                void OnItemAdded(const Eegeo::Resources::Interiors::MetaData::IInteriorMetaDataRepository::ItemType& item);
                void OnItemRemoved(const Eegeo::Resources::Interiors::MetaData::IInteriorMetaDataRepository::ItemType& item);
                
                void OnSelectionChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId);
                
                Eegeo::Helpers::TCallback1<InteriorMenuObserver, const Eegeo::Resources::Interiors::InteriorId> m_interiorSelectionChangedCallback;
                void OnEnterInterior(const Eegeo::Resources::Interiors::InteriorId& interiorId);
                void OnExitInterior();
                void ClearTagSearchRepository();
                void NotifyInteriorTagsUpdated() const;
                void CreateModelsFromConfig(const std::vector<ExampleApp::ApplicationConfig::SdkModel::ApplicationMenuItemTagSearchConfig>& menuItems);
                void ClearDefaultOutdoorTags();
                
                TagSearch::View::ITagSearchRepository& m_tagSearchRepository;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                Eegeo::Resources::Interiors::MetaData::IInteriorMetaDataRepository& m_interiorMetaDataRepo;
                TagSearch::View::TagSearchRepository m_previousTagSearchRepository;
                TransitionState HandleTransitionStates();
                Search::Yelp::SdkModel::YelpCategoryMapperUpdater& m_yelpCategoryMapperUpdater;
                
                bool m_hasSelectedInterior;
                bool m_hasSearchMenuItems;
                bool m_shouldOverrideIndoorSearchMenuItems;

                bool m_loadInteriorOnAdd;
                Eegeo::Resources::Interiors::InteriorId m_idToBeLoaded;
                
                Eegeo::Helpers::CallbackCollection0 m_interiorTagsUpdatedCallbacks;
                std::vector<TagSearch::View::TagSearchModel> m_defaultFindMenuEntries;
                
                std::string m_defaultIconKey;
            };
            
        }
    }
}
