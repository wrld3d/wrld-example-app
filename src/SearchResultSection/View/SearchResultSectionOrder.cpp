// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultSectionOrder.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchParser.h"
#include "InteriorInteractionModel.h"
#include "InteriorMarkerModelRepository.h"
#include "InteriorMarkerModel.h"
#include "InteriorsModel.h"
#include "LatLongAltitude.h"
#include "IAppCameraController.h"
#include "CameraState.h"
#include <limits>

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            namespace
            {                
                int GetSwallowResultPriority(const Search::SdkModel::SearchResultModel& result)
                {
                    if(result.GetPrimaryTag() == Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME)
                    {
                        return Search::SwallowPeopleVendorPriority;
                    }
                    
                    if(result.GetPrimaryTag() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
                    {
                        return Search::SwallowMeetingRoomsVendorPriority;
                    }
                    
                    if(result.GetPrimaryTag() == Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME)
                    {
                        return Search::SwallowWorkingGroupsVendorPriority;
                    }
                    
                    if(result.GetPrimaryTag() == Search::Swallow::SearchConstants::FACILITY_CATEGORY_NAME)
                    {
                        return Search::SwallowFacilitiesVendorPriority;
                    }
                    
                    if(result.GetPrimaryTag() == Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME)
                    {
                        return Search::SwallowOfficesVendorPriority;
                    }
                    
                    return Search::SwallowVendorPriority_MAX;
                }
                
                int GetAvailabilityPriority(const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& meetingroom)
                {
                    if(meetingroom.GetAvailability() == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE)
                    {
                        return Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_PRIORITY;
                    }
                    else if(meetingroom.GetAvailability() == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON)
                    {
                        return Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON_PRIORITY;
                    }
                    else if(meetingroom.GetAvailability() == Search::Swallow::SearchConstants::MEETING_ROOM_OCCUPIED)
                    {
                        return Search::Swallow::SearchConstants::MEETING_ROOM_OCCUPIED_PRIORITY;
                    }
                    
                    return Search::Swallow::SearchConstants::MEETING_ROOM_MAX_PRIORITY;
                }
                
                bool GetFloorOrder(int floorA, int floorB, int currentFloorIndex)
                {
                    int floorDistanceA = currentFloorIndex - floorA;
                    int floorDistanceB = currentFloorIndex - floorB;
                    
                    int absFloorDistanceA = abs(floorDistanceA);
                    int absFloorDistanceB = abs(floorDistanceB);
                    if(absFloorDistanceA == absFloorDistanceB)
                    {
                        return floorDistanceA > floorDistanceB;
                    }
                    
                    return absFloorDistanceA < absFloorDistanceB;
                }
                
                bool GetExteriorOrder(const Eegeo::Resources::Interiors::InteriorId& buildingIdA,
                                      const Eegeo::Resources::Interiors::InteriorId& buildingIdB,
                                      const Eegeo::dv3& cameraFocusLocationEcef,
                                      const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository)
                {
                    bool hasMarkerForA = markerRepository.Contains(buildingIdA);
                    bool hasMarkerForB = markerRepository.Contains(buildingIdB);
                    
                    if(!hasMarkerForA && !hasMarkerForB)
                    {
                        return buildingIdA.Value() < buildingIdB.Value();
                    }
                    
                    double distanceToA = std::numeric_limits<double>::max();
                    double distanceToB = std::numeric_limits<double>::max();
                    
                    if(hasMarkerForA)
                    {
                        Eegeo::dv3 buildingLocationEcef = markerRepository.Get(buildingIdA).GetMarkerLatLongAltitude().ToECEF();
                        distanceToA = (buildingLocationEcef - cameraFocusLocationEcef).LengthSq();
                    }
                    
                    if(hasMarkerForB)
                    {
                        Eegeo::dv3 buildingLocationEcef = markerRepository.Get(buildingIdB).GetMarkerLatLongAltitude().ToECEF();
                        distanceToB = (buildingLocationEcef - cameraFocusLocationEcef).LengthSq();
                    }
                    
                    return distanceToA < distanceToB;
                }
                
                bool GetOrderForMeetingRooms(const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b, int currentFloorIndex)
                {
                    // Meeting room order: Current floor first, ordered by Available, Available Soon and Occupied.
                    // Then Lower floor > Higher floor > 2x Lower floor > ...
                    Search::Swallow::SdkModel::SwallowMeetingRoomResultModel roomA = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(a);
                    Search::Swallow::SdkModel::SwallowMeetingRoomResultModel roomB = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(b);
                    
                    if(a.GetFloor() == b.GetFloor())
                    {
                        int meetingRoomAvailabilityValueA = GetAvailabilityPriority(roomA);
                        int meetingRoomAvailabilityValueB = GetAvailabilityPriority(roomB);
                        
                        return meetingRoomAvailabilityValueA < meetingRoomAvailabilityValueB;
                    }
                    else
                    {
                        return GetFloorOrder(a.GetFloor(), b.GetFloor(), currentFloorIndex);
                    }
                    
                    return false;
                }
                
                bool GetOrderForWorkingGroups(const Search::SdkModel::SearchResultModel& a,
                                              const Search::SdkModel::SearchResultModel& b,
                                              const Eegeo::dv3& cameraFocusLocationEcef,
                                              const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markersRepository,
                                              const Eegeo::Resources::Interiors::InteriorId& currentInteriorId,
                                              int currentFloorIndex)
                {
                    return a.GetTitle() < b.GetTitle();                    
                }
            }
            
        
            
            
            bool GetExteriorOrderForMeetingRooms(const Search::SdkModel::SearchResultModel& a,
                                                 const Search::SdkModel::SearchResultModel& b,
                                                 const Eegeo::dv3& cameraFocusLocationEcef,
                                                 const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository)
            {
                // Closest building then ascending floors. If don't have a position for the building, sort by id.
                bool sameBuilding = a.GetBuildingId() == b.GetBuildingId();
                if(sameBuilding)
                {
                    return GetOrderForMeetingRooms(a, b, 0);
                }
                
                return GetExteriorOrder(a.GetBuildingId(), b.GetBuildingId(), cameraFocusLocationEcef, markerRepository);
            }
            
            SearchResultSectionOrder::SearchResultSectionOrder(const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                               const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& interiorMarkerRepository,
                                                               AppCamera::SdkModel::IAppCameraController& appCameraController
                                                               )
            : m_interiorInteractionModel(interiorInteractionModel)
            , m_interiorMarkerRepository(interiorMarkerRepository)
            , m_appCameraController(appCameraController)
            {
                
            }
            
            bool SearchResultSectionOrder::operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
            {
                //Order eeGeo results on top
                if(a.GetVendor() != b.GetVendor() && a.GetVendor() == Search::EegeoVendorName)
                {
                    return true;
                }
                //Order GeoNames results as they came in
                if(a.GetVendor() == Search::GeoNamesVendorName || b.GetVendor() == Search::GeoNamesVendorName)
                {
                    return false;
                }
                //Order eeGeo results as they came in
                if(a.GetVendor() == Search::EegeoVendorName || b.GetVendor() == Search::EegeoVendorName)
                {
                    bool matchingCategory = a.GetPrimaryTag() == b.GetPrimaryTag() &&
                                            a.GetVendor() == Search::EegeoVendorName &&
                                            b.GetVendor() == Search::EegeoVendorName;
                    
                    if (matchingCategory)
                    {
                        if(a.GetPrimaryTag() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
                        {
                            if(m_interiorInteractionModel.HasInteriorModel())
                            {
                                return GetOrderForMeetingRooms(a, b, m_interiorInteractionModel.GetSelectedFloorIndex());
                            }
                            else
                            {
                                const Eegeo::dv3 cameraFocusLocation = m_appCameraController.GetCameraState().InterestPointEcef();
                                return GetExteriorOrderForMeetingRooms(a, b, cameraFocusLocation, m_interiorMarkerRepository);
                            }
                        }
                        else if(a.GetPrimaryTag() == Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME)
                        {
                            const Eegeo::dv3 cameraFocusLocation = m_appCameraController.GetCameraState().InterestPointEcef();
                            Eegeo::Resources::Interiors::InteriorId currentInteriorId = m_interiorInteractionModel.HasInteriorModel() ? m_interiorInteractionModel.GetInteriorModel()->GetId() : Eegeo::Resources::Interiors::InteriorId::NullId();
                            
                            return GetOrderForWorkingGroups(a, b, cameraFocusLocation, m_interiorMarkerRepository, currentInteriorId, m_interiorInteractionModel.GetSelectedFloorIndex());
                        }
                        
                        return false;
                    }
                    else
                    {
                        int aPriority = GetSwallowResultPriority(a);
                        int bPriority = GetSwallowResultPriority(b);
                        return aPriority < bPriority;
                    }
                }
                return a < b;
            }
            
            
        }
    }
}