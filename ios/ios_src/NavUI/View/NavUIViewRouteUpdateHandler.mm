// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavUIViewRouteUpdateHandler.h"

#include "RoutingQueryOptions.h"

namespace ExampleApp
{
    namespace NavUI
    {
        namespace View
        {
            Eegeo::Routes::Webservice::RoutingQueryWaypoint GetWaypoint(WRLDNavLocation* navLocation)
            {
                CLLocationCoordinate2D waypointLatLng = navLocation.latLon;
                Eegeo::Space::LatLong latLng = Eegeo::Space::LatLong::FromDegrees(waypointLatLng.latitude, waypointLatLng.longitude);
                
                Eegeo::Routes::Webservice::RoutingQueryWaypoint routingQueryWaypoint =
                {
                    latLng,
                    static_cast<bool>(navLocation.indoorID != nil ? true : false),
                    static_cast<int>(navLocation.floorID)
                };
                
                return routingQueryWaypoint;
            }
            
            NSString* GetCurrentInstructionFromType(const std::string& nativeType, const std::string& nativeModifier, bool shouldCapitalize = true)
            {
                NSString *type = [NSString stringWithCString: nativeType.c_str() encoding:NSUTF8StringEncoding];
                NSString *modifier = [NSString stringWithCString: nativeModifier.c_str() encoding:NSUTF8StringEncoding];
                
                if ([type isEqualToString:@"new name"])
                {
                    type = @"turn";
                }
                
                if ([type isEqualToString:@"turn"] && [modifier isEqualToString:@"straight"])
                {
                    return [NSString stringWithFormat: @"Continue %@", modifier];
                }
                
                if ([type isEqualToString:@"turn"] && [modifier isEqualToString:@"uturn"])
                {
                    return @"Make a U-turn";
                }
                
                if (shouldCapitalize)
                {
                    if([type length]<2)
                    {
                        type = [type capitalizedString];
                    }
                    else
                    {
                        type = [NSString stringWithFormat:@"%@%@",[[type substringToIndex:1] uppercaseString],[type substringFromIndex:1]];
                    }
                }
                
                return [NSString stringWithFormat: @"%@ %@", type, modifier];
            }
            
            NSString* GetIconNameFromType(const std::string& nativeType, const std::string& nativeModifier)
            {
                NSString *type = [NSString stringWithCString: nativeType.c_str() encoding:NSUTF8StringEncoding];
                NSString *modifier = [NSString stringWithCString: nativeModifier.c_str() encoding:NSUTF8StringEncoding];
                
                type = [type stringByReplacingOccurrencesOfString:@" " withString:@"_"];
                modifier = [modifier stringByReplacingOccurrencesOfString:@" " withString:@"_"];
                
                if ([type isEqualToString:@"arrive"] || [type isEqualToString:@"depart"])
                {
                    return type;
                }
                
                if ([type isEqualToString:@"new_name"])
                {
                    type = @"turn";
                }
                
                if ([type isEqualToString:@"turn"] && [modifier isEqualToString:@"straight"])
                {
                    return modifier;
                }
                
                return [NSString stringWithFormat: @"%@_%@", type, modifier];
            }
            
            WRLDJourneyRouteDirections* GetDirections(const Eegeo::Routes::Webservice::RouteData& route)
            {
                NSMutableArray<Direction*> *directionsArray = [[NSMutableArray alloc] init];
                
                for (auto& section: route.Sections)
                {
                    int count = static_cast<int>(section.Steps.size());
                    for (int i=0; i<count; i++)
                    {
                        auto& step = section.Steps[i];
                        auto& directions = step.Directions;
                        
                        NSString *currentInstruction = GetCurrentInstructionFromType(directions.Type, directions.Modifier);
                        NSString *nextInstruction = @"Arrived at destination.";
                        
                        if ((i+1)<count)
                        {
                            auto& nextStep = section.Steps[i+1];
                            auto& nextDirections = nextStep.Directions;
                            
                            nextInstruction = [NSString stringWithFormat: @"Then %@",
                                               GetCurrentInstructionFromType(nextDirections.Type, nextDirections.Modifier, false)];
                        }
                        
                        int pathCount = static_cast<int>(step.Path.size());
                        CLLocationCoordinate2D* path = new CLLocationCoordinate2D[pathCount];
                        
                        for (int i=0; i<pathCount; i++)
                        {
                            const Eegeo::Space::LatLong& pathLatLong = step.Path[i];
                            path[i] = CLLocationCoordinate2DMake(pathLatLong.GetLatitudeInDegrees(), pathLatLong.GetLongitudeInDegrees());
                        }
                        
                        NSString *indoorId = [NSString stringWithCString: step.IndoorId.c_str() encoding:NSUTF8StringEncoding];
                        
                        Direction* direction = [[Direction alloc] initDirectionWithName:currentInstruction
                                                                                   icon:GetIconNameFromType(directions.Type, directions.Modifier)
                                                                            instruction:currentInstruction
                                                                        thenInstruction:nextInstruction
                                                                                   path:path
                                                                              pathCount:pathCount
                                                                              isIndoors:static_cast<BOOL>(step.IsIndoors)
                                                                            indoorMapID:indoorId
                                                                                floorId:step.IndoorFloorId];
                        [directionsArray addObject:direction];
                    }
                }
                
                WRLDJourneyRouteDirections *routeDirections = [[WRLDJourneyRouteDirections alloc] initWithEstimatedDuration:route.Duration
                                                                                                                 directions:[directionsArray copy]];
                return routeDirections;
            }
            
            void UpdateDirectionsFromRoute(const Eegeo::Routes::Webservice::RouteData& route, JourneysModel* journeysModel)
            {
                WRLDJourneyRouteDirections* routeDirections = GetDirections(route);
                
                journeysModel.routeDirections = routeDirections;
                journeysModel.estimatedJourneyDuration = routeDirections.estimatedRouteDuration;
                journeysModel.remainingJourneyDuration = routeDirections.estimatedRouteDuration;
                journeysModel.navMode = ([[routeDirections directions] count]>0) ? JourneyNavModeReady : JourneyNavModeNotReady;
            }
            
            NavUIViewRouteUpdateHandler::NavUIViewRouteUpdateHandler(JourneysModel* journeysModel,
                                                                     NavRouteDrawingController& routeDrawingController,
                                                                     NavRoutingServiceController& routingServiceController)
            : m_journeysModel(journeysModel)
            , m_routeDrawingController(routeDrawingController)
            , m_routingServiceController(routingServiceController)
            , m_routesReceivedCallback(this, &NavUIViewRouteUpdateHandler::OnRoutingQueryCompleted)
            {
                m_routingServiceController.RegisterQueryCompletedCallback(m_routesReceivedCallback);
            }
            
            NavUIViewRouteUpdateHandler::~NavUIViewRouteUpdateHandler()
            {
                m_routingServiceController.UnregisterQueryCompletedCallback(m_routesReceivedCallback);
            }
            
            void NavUIViewRouteUpdateHandler::UpdateRoute()
            {
                m_journeysModel.routeDirections = nil;
                m_journeysModel.navMode = JourneyNavModeNotReady;
                
                WRLDNavLocation *startLocation = m_journeysModel.startLocation;
                WRLDNavLocation *endLocation = m_journeysModel.endLocation;
                
                if (startLocation!=nil && endLocation!=nil)
                {
                    std::vector<Eegeo::Routes::Webservice::RoutingQueryWaypoint> waypoints;
                    waypoints.reserve(2);
                    
                    waypoints.emplace_back(GetWaypoint(startLocation));
                    waypoints.emplace_back(GetWaypoint(endLocation));
                    
                    Eegeo::Routes::Webservice::RoutingQueryOptions queryOptions(waypoints);
                    m_routingServiceController.MakeRoutingQuery(queryOptions);
                }
            }
            
            void NavUIViewRouteUpdateHandler::ClearRoute()
            {
                m_routeDrawingController.ClearRoute();
            }
            
            void NavUIViewRouteUpdateHandler::OnRoutingQueryCompleted(const std::vector<Eegeo::Routes::Webservice::RouteData>& results)
            {
                //Only using first route for now
                UpdateDirectionsFromRoute(results[0], m_journeysModel);
                
                m_routeDrawingController.DrawRoute(results[0]);
            }
        }
    }
}
