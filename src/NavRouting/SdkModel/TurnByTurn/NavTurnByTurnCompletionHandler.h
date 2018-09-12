// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavRouting.h"
#include "Location.h"
#include "INavTurnByTurnCompletionHandler.h"
#include "SearchResultModel.h"
#include "InteriorEntityHighlightController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            namespace TurnByTurn
            {
                class NavTurnByTurnCompletionHandler : public INavTurnByTurnCompletionHandler
                {
                public:

                    NavTurnByTurnCompletionHandler(INavTurnByTurnModel& turnByTurnModel,
                                                   INavRoutingModel& navRoutingModel,
                                                   Eegeo::Location::ILocationService& locationService,
                                                   InteriorsExplorer::SdkModel::Highlights::InteriorEntityHighlightController& interiorEntityHighlightController,
                                                   float accuracyMultiplier,
                                                   float minDistanceToFinish);
                    ~NavTurnByTurnCompletionHandler();

                    void HighlightOnCompletion(const Search::SdkModel::SearchResultModel& m_searchResultModel) override;

                private:

                    INavTurnByTurnModel& m_turnByTurnModel;
                    INavRoutingModel& m_navRoutingModel;
                    Eegeo::Location::ILocationService& m_locationService;
                    float m_accuracyMultiplier;
                    float m_minDistanceToFinish;
                    int m_directionCount;
                    InteriorsExplorer::SdkModel::Highlights::InteriorEntityHighlightController& m_interiorEntityHighlightController;

                    Search::SdkModel::SearchResultModel m_completionHighlightModel;
                    
                    Eegeo::Helpers::TCallback0<NavTurnByTurnCompletionHandler> m_turnByTurnStartedCallback;
                    Eegeo::Helpers::TCallback0<NavTurnByTurnCompletionHandler> m_turnByTurnUpdatedCallback;

                    void HandleTurnByTurnStarted();
                    void HandleTurnByTurnUpdated();
                };
            }
        }
    }
}
