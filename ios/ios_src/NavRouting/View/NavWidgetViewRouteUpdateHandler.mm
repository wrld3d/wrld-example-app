// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetViewRouteUpdateHandler.h"

#include "RoutingQueryOptions.h"

namespace ExampleApp
{
    namespace NavRouting
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
            
            WRLDNavRoute* GetDirections(const Eegeo::Routes::Webservice::RouteData& route)
            {
                NSMutableArray<WRLDNavDirection*> *directionsArray = [[NSMutableArray alloc] init];

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
                        NSMutableArray<NSValue *>* path = [[NSMutableArray<NSValue *> alloc] init];

                        for (int i=0; i<pathCount; i++)
                        {
                            const Eegeo::Space::LatLong& pathLatLong = step.Path[i];
                            CLLocationCoordinate2D coord = CLLocationCoordinate2DMake(pathLatLong.GetLatitudeInDegrees(), pathLatLong.GetLongitudeInDegrees());
                            [path addObject:[NSValue valueWithBytes:&coord objCType:@encode(CLLocationCoordinate2D)]];
                        }
                        
                        NSString *indoorId = nil;
                        if(step.IsIndoors)
                        {
                            indoorId = [NSString stringWithCString: step.IndoorId.c_str() encoding:NSUTF8StringEncoding];
                        }
                        
                        
                        WRLDNavDirection* direction =
                        [[WRLDNavDirection alloc]initWithName:currentInstruction
                                                         icon:GetIconNameFromType(directions.Type, directions.Modifier)
                                                  instruction:currentInstruction
                                              thenInstruction:nextInstruction
                                                         path:path
                                                     indoorID:indoorId
                                                      floorID:step.IndoorFloorId
                                                 isMultiFloor:step.IsMultiFloor];
                        [directionsArray addObject:direction];
                    }
                }
                
                WRLDNavRoute *routeDirections =
                [[WRLDNavRoute alloc] initWithEstimatedRouteDuration:route.Duration
                                                          directions:[directionsArray copy]];
                
                return routeDirections;
            }
            
            void UpdateDirectionsFromRoute(const Eegeo::Routes::Webservice::RouteData& route, WRLDNavModel* navModel)
            {
                WRLDNavRoute* navRoute = GetDirections(route);
                
                navModel.route = navRoute;
                navModel.remainingRouteDuration = navRoute.estimatedRouteDuration;
                navModel.navMode = ([[navRoute directions] count]>0) ? WRLDNavModeReady : WRLDNavModeNotReady;
            }
            
            NavWidgetViewRouteUpdateHandler::NavWidgetViewRouteUpdateHandler(WRLDNavModel* navModel,
                                                                     NavRoutingServiceController& routingServiceController)
            : m_navModel(navModel)
            , m_routingServiceController(routingServiceController)
            , m_routesReceivedCallback(this, &NavWidgetViewRouteUpdateHandler::OnRoutingQueryCompleted)
            {
                m_routingServiceController.RegisterQueryCompletedCallback(m_routesReceivedCallback);
            }
            
            NavWidgetViewRouteUpdateHandler::~NavWidgetViewRouteUpdateHandler()
            {
                m_routingServiceController.UnregisterQueryCompletedCallback(m_routesReceivedCallback);
            }
            
            void NavWidgetViewRouteUpdateHandler::UpdateRoute()
            {
                m_navModel.route = nil;
                m_navModel.navMode = WRLDNavModeNotReady;
                
                WRLDNavLocation *startLocation = m_navModel.startLocation;
                WRLDNavLocation *endLocation = m_navModel.endLocation;
                
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
            
            void NavWidgetViewRouteUpdateHandler::OnRoutingQueryCompleted(const std::vector<Eegeo::Routes::Webservice::RouteData>& results)
            {
                //Only using first route for now
                UpdateDirectionsFromRoute(results[0], m_navModel);
            }
        }
    }
}
