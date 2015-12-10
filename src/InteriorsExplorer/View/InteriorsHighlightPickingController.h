// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include "Collision.h"
#include "Rendering.h"
#include "Modules.h"
#include "PickingController.h"
#include "IInteriorController.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "CategorySearchSelectedMessage.h"
#include "SearchResultViewClearedMessage.h"
#include "InteriorsExplorerEnteredMessage.h"
#include "InteriorsExplorerExitMessage.h"
#include "SdkModelDomainEventBus.h"
#include "SwallowPoiDbServiceProvider.h"
#include "SearchQuery.h"
#include "SearchQueryResponseReceivedMessage.h"

#include <vector>
#include <string>

namespace ExampleApp
{
    namespace Picking
    {
        class InteriorsHighlightPickingController : public Eegeo::Picking::PickingController
        {
        public:
            InteriorsHighlightPickingController(Eegeo::Collision::IRayCaster& rayCaster,
                                       Eegeo::Resources::Interiors::IInteriorController& interiorController,
                                       Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                       ExampleAppMessaging::TMessageBus& messageBus,
                                       ExampleAppMessaging::TSdkModelDomainEventBus& domainBus);
            
            ~InteriorsHighlightPickingController();
            
            void ProcessRayCastResult(const Eegeo::Collision::RayCasterResult& pickResult);
            
        private:
            void OnCategorySearchPerformed(const CategorySearch::CategorySearchSelectedMessage& message);
            void OnSearchResultCleared(const SearchResultMenu::SearchResultViewClearedMessage& message);
            void OnInteriorsEntered(const InteriorsExplorer::InteriorsExplorerEnteredMessage& message);
            void OnInteriorsExited(const InteriorsExplorer::InteriorsExplorerExitMessage& message);
            void OnAvailabilityChanged(const ExampleApp::SearchResultOnMap::SearchResultMeetingAvailabilityChanged& message);
            void OnSearchResultsLoaded(const Search::SearchQueryResponseReceivedMessage& message);
            
            void ConfigureRenderableForAvailability(Eegeo::Rendering::Renderables::InteriorHighlightRenderable& renderable, const std::string& availability);
            void DeactivateHighlightRenderables();
            void AddHighlight(Eegeo::Rendering::Renderables::InteriorHighlightRenderable& renderable);

            Eegeo::Resources::Interiors::IInteriorController& m_interiorsController;
            
            ExampleAppMessaging::TMessageBus& m_messageBus;
            ExampleAppMessaging::TSdkModelDomainEventBus& m_domainBus;
            
            Eegeo::Helpers::TCallback1<InteriorsHighlightPickingController, const CategorySearch::CategorySearchSelectedMessage&> m_categorySearchHandlerBinding;
            Eegeo::Helpers::TCallback1<InteriorsHighlightPickingController, const SearchResultMenu::SearchResultViewClearedMessage&> m_searchResultHandlerBinding;
            Eegeo::Helpers::TCallback1<InteriorsHighlightPickingController, const InteriorsExplorer::InteriorsExplorerEnteredMessage&> m_interiorsHandlerBinding;
            Eegeo::Helpers::TCallback1<InteriorsHighlightPickingController, const InteriorsExplorer::InteriorsExplorerExitMessage&> m_interiorsExitHandlerBinding;
            Eegeo::Helpers::TCallback1<InteriorsHighlightPickingController, const ExampleApp::SearchResultOnMap::SearchResultMeetingAvailabilityChanged&>m_availabilityChangedHandlerBinding;
            Eegeo::Helpers::TCallback1<InteriorsHighlightPickingController, const Search::SearchQueryResponseReceivedMessage&> m_searchResultReceivedHandler;
            
            std::map<std::string, std::string> m_highlightAvailabilityData;
            std::map<std::string, Eegeo::Rendering::Renderables::InteriorHighlightRenderable*> m_currentHighlightRenderables;
        };
    }
}