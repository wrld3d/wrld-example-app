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
                    if(document.HasMember("search_menu_items") && document["search_menu_items"].IsObject())
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
                        
                        if(transtionState == TransitionState::EnteringBuilding)
                        {
                            size_t size = m_tagSearchRepository.GetItemCount();
                            for(auto i = size; i > 0; i--)
                            {
                                m_tagSearchRepository.RemoveItem(m_tagSearchRepository.GetItemAtIndex(i-1));
                            }
                        }
                        else if(transtionState == TransitionState::SwitchingBuilding)
                        {
                            ClearTagSearchModelTracker();
                        }
                        
                        size_t repoSize = m_tagSearchRepository.GetItemCount();
                        Eegeo_TTY("hi, %d", repoSize);
                        
                        if(searchMenuItems.HasMember("items") && searchMenuItems["items"].IsArray())
                        {
                            const rapidjson::Value& menuItems = searchMenuItems["items"];
                            for(rapidjson::SizeType i = 0; i < menuItems.Size(); i++)
                            {
                                const TagSearch::View::TagSearchModel* v =
                                Eegeo_NEW(TagSearch::View::TagSearchModel(menuItems[i]["name"].GetString(), menuItems[i]["search_tag"].GetString(), true, menuItems[i]["icon_key"].GetString(), true));
                                m_tagSearchModelTracker.push_back(v);
                                m_tagSearchRepository.AddItem(*v);
                            }
                        }
                        
                        repoSize = m_tagSearchRepository.GetItemCount();
                        Eegeo_TTY("hi, %d", repoSize);
                    }
                }
            }
            void InteriorMenuObserver::ClearTagSearchModelTracker()
            {
                size_t size = m_tagSearchModelTracker.size();
                for(auto i = size; i > 0; i--)
                {
                    const TagSearch::View::TagSearchModel& searchRepo = m_tagSearchRepository.GetItemAtIndex(i-1);
                    m_tagSearchRepository.RemoveItem(searchRepo);
                    Eegeo_DELETE m_tagSearchModelTracker[i-1];
                }
                m_tagSearchModelTracker.clear();
            }
            
            void InteriorMenuObserver::OnExitInterior()
            {
                ClearTagSearchModelTracker();
                
                size_t repoSize = m_tagSearchRepository.GetItemCount();
                Eegeo_TTY("hi, %d", repoSize);
                
                for(auto i = 0; i < m_previousTagSearchRepository.GetItemCount(); i++)
                {
                    m_tagSearchRepository.AddItem(m_previousTagSearchRepository.GetItemAtIndex(i));
                }
                
                repoSize = m_tagSearchRepository.GetItemCount();
                Eegeo_TTY("hi, %d", repoSize);
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