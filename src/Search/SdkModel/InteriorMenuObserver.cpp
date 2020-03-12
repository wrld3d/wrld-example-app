// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfigurationJsonParser.h"
#include "InteriorMenuObserver.h"
#include "TagSearchModel.h"
#include "document.h"
#include "writer.h"
#include "YelpCategoryModel.h"
#include "IInteriorMetaDataService.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            InteriorMenuObserver::InteriorMenuObserver(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                       Eegeo::Resources::Interiors::MetaData::IInteriorMetaDataService& interiorMetaDataService,
                                                       TagSearch::View::ITagSearchRepository& tagSearchRepository,
                                                       Search::Yelp::SdkModel::YelpCategoryMapperUpdater& yelpCategoryMapperUpdater,
                                                       std::vector<TagSearch::View::TagSearchModel> defaultFindMenuEntries,
                                                       Search::SdkModel::TagIconKey defaultIconKey)
            : m_tagSearchRepository(tagSearchRepository)
            , m_interiorSelectionChangedCallback(this, &InteriorMenuObserver::OnSelectionChanged)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorMetaDataService(interiorMetaDataService)
            , m_hasSelectedInterior(false)
            , m_hasSearchMenuItems(false)
            , m_yelpCategoryMapperUpdater(yelpCategoryMapperUpdater)
            , m_defaultFindMenuEntries(defaultFindMenuEntries)
            , m_loadInteriorOnAdd(false)
            , m_shouldOverrideIndoorSearchMenuItems(false)
            , m_idToBeLoaded()
            , m_defaultIconKey(defaultIconKey)
            , m_interiorMetaDataAddedHandler(this, &InteriorMenuObserver::OnInteriorMetaDataAdded)
            , m_interiorMetaDataRemovedHandler(this, &InteriorMenuObserver::OnInteriorMetaDataRemoved)
            {
                m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorSelectionChangedCallback);
                m_hasSelectedInterior = m_interiorSelectionModel.IsInteriorSelected();
                m_interiorMetaDataService.GetInteriorMetaDataModelAddedEvent().Register(m_interiorMetaDataAddedHandler);
                m_interiorMetaDataService.GetInteriorMetaDataModelRemovedEvent().Register(m_interiorMetaDataRemovedHandler);
            }
            
            InteriorMenuObserver::~InteriorMenuObserver()
            {
                m_interiorMetaDataService.GetInteriorMetaDataModelAddedEvent().Unregister(m_interiorMetaDataAddedHandler);
                m_interiorMetaDataService.GetInteriorMetaDataModelRemovedEvent().Unregister(m_interiorMetaDataRemovedHandler);
                m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorSelectionChangedCallback);
            }

            void InteriorMenuObserver::OnInteriorMetaDataAdded(const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataModelMessage& message)
            {
                if (m_loadInteriorOnAdd && m_interiorMetaDataService.Exists(m_idToBeLoaded.Value()))
                {
                    OnEnterInterior(m_idToBeLoaded);
                    m_loadInteriorOnAdd = false;
                }
            }

            void InteriorMenuObserver::OnInteriorMetaDataRemoved(const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataModelMessage& message)
            {

            }

            void InteriorMenuObserver::OnSelectionChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                TransitionState transitionState = HandleTransitionStates();
                if(transitionState == TransitionState::LeavingBuilding)
                {
                    OnExitInterior();
                }
                else if (!m_interiorMetaDataService.Exists(interiorId.Value()))
                {
                    m_loadInteriorOnAdd = true;
                    m_idToBeLoaded = interiorId;
                }
                else if (transitionState == TransitionState::EnteringBuilding || transitionState == TransitionState::SwitchingBuilding)
                {
                    OnEnterInterior(interiorId);
                }
                
                NotifyInteriorTagsUpdated();
            }
            
            void InteriorMenuObserver::ApplyCustomInteriorSearchMenuItems(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                std::string user_data;
                if (!m_interiorMetaDataService.TryGetUserData(interiorId.Value(), user_data))
                {
                    return;
                }

                rapidjson::Document document;
                if (!document.Parse<0>(user_data.c_str()).HasParseError())
                {
                    m_hasSearchMenuItems = document.HasMember("search_menu_items") && document["search_menu_items"].IsObject();
                    if(m_hasSearchMenuItems)
                    {
                        const rapidjson::Value& searchMenuItems = document["search_menu_items"];
                        
                        if(m_previousTagSearchRepository.GetItemCount() == 0)
                        {
                            for(auto i = 0; i < m_tagSearchRepository.GetItemCount(); i++)
                            {
                                m_previousTagSearchRepository.AddItem(m_tagSearchRepository.GetItemAtIndex(i));
                            }
                        }
                        
                        ClearTagSearchRepository();
                        
                        if(searchMenuItems.HasMember("items") && searchMenuItems["items"].IsArray())
                        {
                            m_yelpCategoryMapperUpdater.ResetMapping();
                            const auto& menuItems = ExampleApp::ApplicationConfig::SdkModel::ApplicationConfigurationJsonParser::ParseSearchMenuConfig(searchMenuItems["items"]);

                            for(auto iter = menuItems.cbegin(); iter != menuItems.cend(); iter++)
                            {
                                if(iter->skipYelp)
                                {
                                    Search::Yelp::SdkModel::YelpCategoryModel yelpCategoryModel { "unused_string", true };
                                    m_yelpCategoryMapperUpdater.AddMapping(iter->searchTag, yelpCategoryModel);
                                }
                                else if(iter->yelpMapping.length() > 0 && iter->yelpMapping != "unused_string")
                                {
                                    Search::Yelp::SdkModel::YelpCategoryModel yelpCategoryModel { iter->yelpMapping, false };
                                    m_yelpCategoryMapperUpdater.AddMapping(iter->searchTag, yelpCategoryModel);
                                }
                                
                                m_tagSearchRepository.AddItem(TagSearch::View::TagSearchModel(iter->name, iter->searchTag, true, iter->iconKey, true));
                            }
                        }
                    }
                }
            }
            
            void InteriorMenuObserver::OnEnterInterior(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                if(!m_shouldOverrideIndoorSearchMenuItems)
                {
                    ApplyCustomInteriorSearchMenuItems(interiorId);
                }
            }
            void InteriorMenuObserver::ClearTagSearchRepository()
            {
                for(auto i = m_tagSearchRepository.GetItemCount(); i > 0; i--)
                {
                    if (i <= m_tagSearchRepository.GetItemCount())
                    {
                        m_tagSearchRepository.RemoveItem(m_tagSearchRepository.GetItemAtIndex(i-1));
                    }
                }
            }
            
            void InteriorMenuObserver::ClearDefaultOutdoorTags()
            {
                for(auto i = m_previousTagSearchRepository.GetItemCount(); i > 0; i--)
                {
                    if (i <= m_previousTagSearchRepository.GetItemCount())
                    {
                        const TagSearch::View::TagSearchModel& searchRepo = m_previousTagSearchRepository.GetItemAtIndex(i-1);
                        m_previousTagSearchRepository.RemoveItem(searchRepo);
                    }
                }
            }

            void InteriorMenuObserver::CreateModelsFromConfig(const std::vector<ExampleApp::ApplicationConfig::SdkModel::ApplicationMenuItemTagSearchConfig>& menuItems)
            {
                ClearTagSearchRepository();
                ClearDefaultOutdoorTags();

                const bool visibleInSearchMenu = true;
                const bool interior = true;
                m_yelpCategoryMapperUpdater.ResetMapping();

                for(auto iter = menuItems.cbegin(); iter != menuItems.cend(); iter++)
                {
                    if(iter->skipYelp)
                    {
                        Search::Yelp::SdkModel::YelpCategoryModel yelpCategoryModel { "unused_string", true };
                        m_yelpCategoryMapperUpdater.AddMapping(iter->searchTag, yelpCategoryModel);
                    }
                    else if(iter->yelpMapping.length() > 0 && iter->yelpMapping != "unused_string")
                    {
                        Search::Yelp::SdkModel::YelpCategoryModel yelpCategoryModel { iter->yelpMapping, false };
                        m_yelpCategoryMapperUpdater.AddMapping(iter->searchTag, yelpCategoryModel);
                    }
                    
                    auto icon = iter->iconKey.length() == 0 ? m_defaultIconKey : iter->iconKey;
                    
                    m_tagSearchRepository.AddItem(TagSearch::View::TagSearchModel(iter->name, iter->searchTag, interior , icon, visibleInSearchMenu));
                    m_previousTagSearchRepository.AddItem(TagSearch::View::TagSearchModel(iter->name, iter->searchTag, interior, icon, visibleInSearchMenu));
                }

                const bool shouldUseDefaultFindMenuEntries = menuItems.size() == 0;
                if (shouldUseDefaultFindMenuEntries)
                {
                    for (auto& item : m_defaultFindMenuEntries)
                    {
                        m_tagSearchRepository.AddItem(item);
                        m_previousTagSearchRepository.AddItem(item);
                    }
                }
            }

            
            void InteriorMenuObserver::UpdateDefaultOutdoorSearchMenuItems(
                    const std::vector<ExampleApp::ApplicationConfig::SdkModel::ApplicationMenuItemTagSearchConfig>& menuItems,
                    bool overrideIndoorSearchMenuItems
            )
            {
                
                CreateModelsFromConfig(menuItems);
                m_shouldOverrideIndoorSearchMenuItems = overrideIndoorSearchMenuItems;
                NotifyInteriorTagsUpdated();
            }
            
            void InteriorMenuObserver::OnExitInterior()
            {
                if(m_hasSearchMenuItems)
                {
                    ClearTagSearchRepository();
                    
                    for(auto i = 0; i < m_previousTagSearchRepository.GetItemCount(); i++)
                    {
                        m_tagSearchRepository.AddItem(m_previousTagSearchRepository.GetItemAtIndex(i));
                    }
                }
            }
            
            InteriorMenuObserver::TransitionState InteriorMenuObserver::HandleTransitionStates()
            {
                if(m_hasSelectedInterior == false && m_interiorSelectionModel.IsInteriorSelected() == true)
                {
                    m_hasSelectedInterior = true;
                    return TransitionState::EnteringBuilding;
                }
                else if(m_hasSelectedInterior == true && m_interiorSelectionModel.IsInteriorSelected() == false)
                {
                    m_hasSelectedInterior = false;
                    return TransitionState::LeavingBuilding;
                }
                else if(m_hasSelectedInterior == true && m_interiorSelectionModel.IsInteriorSelected() == true)
                {
                    return TransitionState::SwitchingBuilding;
                }
                else
                {
                    return TransitionState::NoTransition;
                }
            }
            
            void InteriorMenuObserver::RegisterInteriorTagsUpdatedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_interiorTagsUpdatedCallbacks.AddCallback(callback);
            }
            
            void InteriorMenuObserver::UnregisterInteriorTagsUpdatedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_interiorTagsUpdatedCallbacks.RemoveCallback(callback);
            }
            
            void InteriorMenuObserver::NotifyInteriorTagsUpdated() const
            {
                m_interiorTagsUpdatedCallbacks.ExecuteCallbacks();
            }
        }
    }
}
