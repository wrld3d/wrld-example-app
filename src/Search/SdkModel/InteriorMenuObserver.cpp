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
                if (document.HasMember(itemKey) && document[itemKey].IsArray())
                {
                    const auto& tagSearchModelsMember = document[itemKey];
                    
                    ClearTagSearchRepository();
                    ClearDefaultOutdoorTags();
                    
                    const bool visibleInSearchMenu = true;
                    const bool interior = true;
                    for (rapidjson::Value::ConstValueIterator it = tagSearchModelsMember.Begin();
                         it != tagSearchModelsMember.End();
                         ++it)
                    {
                        const auto& item = *it;
                        
                        const char* nameKey = "name";
                        if(!item.HasMember(nameKey) || !item[nameKey].IsString())
                        {
                            Eegeo_TTY("no member 'name' or is not a string");
                            break;
                        }
                        const std::string& name = item[nameKey].GetString();
                        
                        const char* searchTagKey = "search_tag";
                        if(!item.HasMember(searchTagKey) || !item[searchTagKey].IsString())
                        {
                            Eegeo_TTY("no member search_tag or is not a string");
                            break;
                        }
                        const std::string& searchTag = item[searchTagKey].GetString();
                        
                        const char* iconKey = "icon_key";
                        if(!item.HasMember(iconKey) || !item[iconKey].IsString())
                        {
                            Eegeo_TTY("no member icon_key or is not a string");
                            break;
                        }
                        const std::string& icon = item[iconKey].GetString();
                      

                        m_tagSearchRepository.AddItem(TagSearch::View::TagSearchModel(name, searchTag, interior, icon, visibleInSearchMenu));
                        m_previousTagSearchRepository.AddItem(TagSearch::View::TagSearchModel(name, searchTag, interior, icon, visibleInSearchMenu));
                    }
                }
                else
                {
                    Eegeo_TTY("outdoor_search_menu_items not a member or not an array");
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