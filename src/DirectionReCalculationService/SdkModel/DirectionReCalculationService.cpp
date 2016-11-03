// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "DirectionReCalculationService.h"

#include <vector>
#include "Route.h"

namespace ExampleApp
{
    namespace DirectionReCalculationService
    {
        namespace SdkModel
        {
            DirectionReCalculationService::DirectionReCalculationService( Eegeo::Location::ILocationService& locationService,ExampleApp::PathDrawing::IPathDrawingController& pathDrawingController)
            : m_locationService(locationService)
            , m_pathDrawingController(pathDrawingController)
            {
            
            }
            
            DirectionReCalculationService::~DirectionReCalculationService()
            {
            
            }
            
            void DirectionReCalculationService::Update(float dt)
            {
                if(m_pathDrawingController.IsRouteCreated())
                {
                    std::vector<Eegeo::Routes::Route*>& routes = m_pathDrawingController.GetCreatedRoutes();
                    if (routes.size() > 0)
                    {
                        Eegeo::Routes::Route* route = routes[0];
                        Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromDegrees(56.459905999999997, -2.9840330000000002);
                        m_locationService.GetIsAuthorized();
                        double out_closestApproch;
                        int out_immedeiatly_before;
                        double distance = Eegeo::Routes::Route::DistanceToRoute(route->GetPoints(),latLong.ToECEF(),out_closestApproch,out_immedeiatly_before);
                        if (distance >= 30)
                        {
                            // call for recalculations
                        }
                        
                    }
                }
            }
        }
    }
}