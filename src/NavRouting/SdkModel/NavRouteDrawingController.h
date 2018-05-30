// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INavRouteDrawingController.h"
#include "INavRoutingModel.h"
#include "VectorMath.h"
#include "NavRouting.h"
#include "NavRoutingDirectionModel.h"
#include "INavRoutingPolylineFactory.h"
#include "Markers.h"
#include "IMarker.h"
#include "IMarkerService.h"

#include <vector>
#include <unordered_map>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRouteDrawingController : public INavRouteDrawingController, private Eegeo::NonCopyable
            {
            public:
                NavRouteDrawingController(INavRoutingModel& navRoutingModel,
                                          INavRoutingPolylineFactory& polylineFactory,
                                          PolyLineArgs::IShapeService& shapeService,
                                          Eegeo::Markers::IMarkerService& markerService);

                ~NavRouteDrawingController() override;
                
                void DrawRoute(const Eegeo::v4& color) override;
                
                void ClearRoute() override;
                
                void SetRouteStepColor(int step, const Eegeo::v4& color) override;
                
                void UpdateRouteStepProgress(int step,
                                             const Eegeo::v4& colorForCrossedPath,
                                             const Eegeo::v4& colorForUpcomingPath,
                                             int splitIndex,
                                             const Eegeo::Space::LatLong& closestPointOnRoute) override;
                
            private:
                
                INavRoutingModel& m_navRoutingModel;
                INavRoutingPolylineFactory& m_polylineFactory;
                PolyLineArgs::IShapeService& m_shapeService;
                std::unordered_map<int, RouteLines> m_routes;
                
                std::map<std::string, std::string> m_directionIconToPinIcon;
                
                Eegeo::Markers::IMarkerService& m_markerService;
                std::vector<Eegeo::Markers::IMarker::IdType> m_markerIDs;
                
                void DrawRouteForStep(int step,
                                      const std::vector<NavRoutingDirectionModel>& directions,
                                      const Eegeo::v4& color);
                
                void DrawRouteForStep(int step,
                                      const std::vector<NavRoutingDirectionModel>& directions,
                                      const Eegeo::v4& forwardColor,
                                      const Eegeo::v4& backwardColor,
                                      int splitIndex,
                                      const Eegeo::Space::LatLong& closestPointOnRoute);
                
                void DestroyLines(RouteLines lines);
                
                void AddPin(bool interior,
                            const std::string& buildingID,
                            const int& buildingfloor,
                            const Eegeo::Space::LatLong& location,
                            const std::string& pinIconKey,
                            float heightAboveTerrainMetres);
                
                //void AddHighlightPin(const Eegeo::Markers::IMarker& marker, std::string labelStyleName);

                void ClearPins();
            };
        }
    }
}
