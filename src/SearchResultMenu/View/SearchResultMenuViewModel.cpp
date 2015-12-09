// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuViewModel.h"
#include "IMenuModel.h"
#include "ISearchQueryPerformer.h"
#include "ISearchService.h"
#include "IReactionControllerModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchResultMenuViewModel::SearchResultMenuViewModel(bool isInitiallyOnScreen,
                                                                 Eegeo::Helpers::TIdentity identity,
                                                                 Reaction::View::IReactionControllerModel& reactionControllerModel)
                : Menu::View::MenuViewModel(isInitiallyOnScreen, identity, reactionControllerModel)
                , m_reactionControllerModel(reactionControllerModel)
                , m_hasSearchQuery(false)
                , m_enabled(true)
            {
            }

            SearchResultMenuViewModel::~SearchResultMenuViewModel()
            {
            }

            bool SearchResultMenuViewModel::CanShowOnScreen() const
            {
                if(!m_hasSearchQuery || !m_enabled)
                {
                    return false;
                }

                if(m_reactionControllerModel.IsAnyOpenableOpen())
                {
                    return m_reactionControllerModel.IsOpenableOpen(GetIdentity());
                }

                return true;
            }

            bool SearchResultMenuViewModel::CanInteract() const
            {
                return CanShowOnScreen() && !m_hasSearchQueryInFlight;
            }

            void SearchResultMenuViewModel::AddToScreen()
            {
                if(CanShowOnScreen())
                {
                    if(!IsAddedToScreen())
                    {
                        Menu::View::MenuViewModel::AddToScreen();
                    }
                }
            }

            void SearchResultMenuViewModel::RemoveFromScreen()
            {
                Menu::View::MenuViewModel::RemoveFromScreen();
            }

            void SearchResultMenuViewModel::SetHasSearchQuery(bool hasSearchQuery)
            {
                m_hasSearchQuery = hasSearchQuery;

                if(m_hasSearchQuery && m_enabled)
                {
                    AddToScreen();
                }
                else
                {
                    RemoveFromScreen();
                }
            }

            void SearchResultMenuViewModel::SetHasSearchQueryInFlight(bool hasSearchQueryInFlight)
            {
            	m_hasSearchQueryInFlight = hasSearchQueryInFlight;
            }
            
            void SearchResultMenuViewModel::EnterAttractMode()
            {
                SetAttractMode(true);
            }
            
            void SearchResultMenuViewModel::ExitAttractMode()
            {
                SetAttractMode(false);
            }
            
            void SearchResultMenuViewModel::SetAttractMode(bool attractModeEnabled)
            {
                bool attractModeChanged = m_inAttractMode != attractModeEnabled;
                m_inAttractMode = attractModeEnabled;
                
                if(attractModeChanged)
                {
                    m_attractModeChangedCallbacks.ExecuteCallbacks();
                }
            }
            
            bool SearchResultMenuViewModel::AttractModeEnabled() const
            {
                return m_inAttractMode;
            }
            
            void SearchResultMenuViewModel::SetEnabled(bool enabled)
            {
                bool hasChanged = m_enabled != enabled;
                m_enabled = enabled;
                
                if(hasChanged)
                {
                    if(m_enabled && (m_hasSearchQuery || m_hasSearchQueryInFlight))
                    {
                        AddToScreen();
                    }
                    else if(!m_enabled)
                    {
                        RemoveFromScreen();
                    }
                }
            }
            
            void SearchResultMenuViewModel::InsertAttractModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_attractModeChangedCallbacks.AddCallback(callback);
            }
            
            void SearchResultMenuViewModel::RemoveAttractModeChangedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_attractModeChangedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
