//
// Created by malcolm.brown on 31/05/2018.
//

#pragma once

#include "ILocationService.h"
#include "InteriorId.h"
#include "Space.h"
#include "NavRouting.h"
#include "ICallback.h"
#include "DebugRendering.h"
#include "Interiors.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            namespace TurnByTurn
            {
                // Use interpolated turn by turn position + heading, but feed it via other ILS


                class NavTurnByTurnLocationService : public Eegeo::Location::ILocationService {
                public:

                    NavTurnByTurnLocationService(
                            INavTurnByTurnModel& turnByTurnModel,
                            INavRoutingModel& navRoutingModel,
                            Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                            Eegeo::DebugRendering::DebugRenderer& debugRenderer);
                    ~NavTurnByTurnLocationService();

                    void SetLocationService(Eegeo::Location::ILocationService& internalLocationService);

                    const bool GetIsAuthorized() const;

                    bool IsIndoors();
                    Eegeo::Resources::Interiors::InteriorId GetInteriorId();

                    bool GetLocation(Eegeo::Space::LatLong& latlong);
                    bool GetAltitude(double& altitude);
                    bool GetFloorIndex(int& floorIndex);
                    bool GetHorizontalAccuracy(double& accuracy);
                    bool GetHeadingDegrees(double& headingDegrees);

                    void StopListening();
                    void Update(float dt);

                private:

                    Eegeo::Helpers::TCallback0<NavTurnByTurnLocationService> m_turnByTurnStartedCallback;
                    Eegeo::Helpers::TCallback0<NavTurnByTurnLocationService> m_turnByTurnEndedCallback;
                    Eegeo::Helpers::TCallback0<NavTurnByTurnLocationService> m_turnByTurnUpdatedCallback;

                    void OnTurnByTurnStarted();
                    void OnTurnByTurnEnded();
                    void OnTurnByTurnUpdated();

                    const Eegeo::Routes::Webservice::RouteStep& GetCurrentRouteStep();
                    const Eegeo::Routes::Webservice::RouteStep& GetNextRouteStep();

                    Eegeo::Location::ILocationService* m_pInternalLocationService;
                    INavTurnByTurnModel& m_turnByTurnModel;
                    INavRoutingModel& m_navRoutingModel;
                    Eegeo::Resources::Interiors::InteriorsModelRepository& m_interiorsModelRepository;
                    Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;

                    float m_targetHeading;
                    float m_currentHeading;
                    bool m_followingRoute;
                    bool m_debugRenderingEnabled;
                };

            }
        }
    }
}

