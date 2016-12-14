// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorMenuObserver.h"
#include "TagSearchModel.h"
#include "document.h"
#include "writer.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            InteriorMenuObserver::InteriorMenuObserver(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                       Eegeo::Resources::Interiors::MetaData::IInteriorMetaDataRepository& interiorMetaDataRepo,
                                                       TagSearch::View::ITagSearchRepository& tagSearchRepository)
            : m_tagSearchRepository(tagSearchRepository)
            , m_interiorSelectionChangedCallback(this, &InteriorMenuObserver::OnSelectionChanged)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorMetaDataRepo(interiorMetaDataRepo)
            , m_hasSelectedInterior(false)
            , m_defaultTagsSaved(false)
            , m_hasSearchMenuItems(false)
            {
                m_interiorSelectionModel.RegisterSelectionChangedCallback(m_interiorSelectionChangedCallback);
                m_hasSelectedInterior = m_interiorSelectionModel.IsInteriorSelected();
            }
            
            InteriorMenuObserver::~InteriorMenuObserver()
            {
                m_interiorSelectionModel.UnregisterSelectionChangedCallback(m_interiorSelectionChangedCallback);
            }
            
            void InteriorMenuObserver::OnSelectionChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId)
            {
                TransitionState transitionState = HandleTransitionStates();
                if(transitionState == TransitionState::LeavingBuilding)
                {
                    OnExitInterior();
                }
                else if (m_interiorMetaDataRepo.Contains(interiorId) && (transitionState == TransitionState::EnteringBuilding || transitionState == TransitionState::SwitchingBuilding))
                {
                    OnEnterInterior(interiorId, transitionState);
                }
                
                NotifyInteriorTagsUpdated();
            }
            
            void InteriorMenuObserver::OnEnterInterior(const Eegeo::Resources::Interiors::InteriorId& interiorId, const TransitionState& transtionState)
            {
                const Eegeo::Resources::Interiors::MetaData::InteriorMetaDataDto* dto = m_interiorMetaDataRepo.Get(interiorId);
                
                std::string user_data = "";
                user_data = dto->GetUserData();
                rapidjson::Document document;
                if (!document.Parse<0>(user_data.c_str()).HasParseError())
                {
                    m_hasSearchMenuItems = document.HasMember("search_menu_items") && document["search_menu_items"].IsObject();
                    if(m_hasSearchMenuItems)
                    {
                        const rapidjson::Value& searchMenuItems = document["search_menu_items"];
                        
                        if(!m_defaultTagsSaved)
                        {
                            for(auto i = 0; i < m_tagSearchRepository.GetItemCount(); i++)
                            {
                                m_previousTagSearchRepository.AddItem(m_tagSearchRepository.GetItemAtIndex(i));
                            }
                            m_defaultTagsSaved = true;
                        }
                        
                        ClearTagSearchRepository();
                        
                        if(searchMenuItems.HasMember("items") && searchMenuItems["items"].IsArray())
                        {
                            const rapidjson::Value& menuItems = searchMenuItems["items"];
                            for(rapidjson::SizeType i = 0; i < menuItems.Size(); i++)
                            {
                                m_tagSearchRepository.AddItem(TagSearch::View::TagSearchModel(menuItems[i]["name"].GetString(), menuItems[i]["search_tag"].GetString(), true, menuItems[i]["icon_key"].GetString(), true));
                            }
                        }
                    }
                }
            }
            void InteriorMenuObserver::ClearTagSearchRepository()
            {
                for(auto i = m_tagSearchRepository.GetItemCount(); i > 0; i--)
                {
                    m_tagSearchRepository.RemoveItem(m_tagSearchRepository.GetItemAtIndex(i-1));
                }
            }
            
            void InteriorMenuObserver::ClearDefaultOutdoorTags()
            {
                for(auto i = m_previousTagSearchRepository.GetItemCount(); i > 0; i--)
                {
                    const TagSearch::View::TagSearchModel& searchRepo = m_previousTagSearchRepository.GetItemAtIndex(i-1);
                    m_previousTagSearchRepository.RemoveItem(searchRepo);
                }
            }
            
            void InteriorMenuObserver::ParseJson(const std::string config)
            {
                rapidjson::Document document;
                
                if (document.Parse<0>(config.c_str()).HasParseError())
                {
                    Eegeo_ASSERT(false, "failed to parse json");
                    return;
                }
                
                const char* itemKey = "outdoor_search_menu_items";
                Eegeo_ASSERT(document.HasMember(itemKey));
                
                const auto& tagSearchModelsMember = document[itemKey];
                Eegeo_ASSERT(tagSearchModelsMember.IsArray());
                
                ClearTagSearchRepository();
                ClearDefaultOutdoorTags();
                
                for (rapidjson::Value::ConstValueIterator it = tagSearchModelsMember.Begin();
                     it != tagSearchModelsMember.End();
                     ++it)
                {
                    const auto& item = *it;
                    
                    const char* nameKey = "name";
                    Eegeo_ASSERT(item.HasMember(nameKey));
                    Eegeo_ASSERT(item[nameKey].IsString());
                    const std::string& name = item[nameKey].GetString();
                    
                    const char* searchTagKey = "search_tag";
                    Eegeo_ASSERT(item.HasMember(searchTagKey));
                    Eegeo_ASSERT(item[searchTagKey].IsString());
                    const std::string& searchTag = item[searchTagKey].GetString();
                    
                    const char* iconKey = "icon_key";
                    Eegeo_ASSERT(item.HasMember(iconKey));
                    Eegeo_ASSERT(item[iconKey].IsString());
                    const std::string& icon = item[iconKey].GetString();
                    
                    const bool visibleInSearchMenu = true;
                    const bool interior = true;

                    m_tagSearchRepository.AddItem(TagSearch::View::TagSearchModel(name, searchTag, interior, icon, visibleInSearchMenu));
                    m_previousTagSearchRepository.AddItem(TagSearch::View::TagSearchModel(name, searchTag, interior, icon, visibleInSearchMenu));
                }
            }

            
            void InteriorMenuObserver::UpdateDefaultOutdoorSearchMenuItems(const std::string config)
            {
                ParseJson(config);
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