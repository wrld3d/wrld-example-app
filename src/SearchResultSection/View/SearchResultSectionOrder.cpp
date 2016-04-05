// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultSectionOrder.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchParser.h"
#include "InteriorInteractionModel.h"
#include "InteriorMarkerModelRepository.h"
#include "InteriorMarkerModel.h"
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
                    if(result.GetCategory() == Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME)
                    {
                        return Search::SwallowPeopleVendorPriority;
                    }
                    
                    if(result.GetCategory() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
                    {
                        return Search::SwallowMeetingRoomsVendorPriority;
                    }
                    
                    if(result.GetCategory() == Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME)
                    {
                        return Search::SwallowWorkingGroupsVendorPriority;
                    }
                    
                    if(result.GetCategory() == Search::Swallow::SearchConstants::FACILITY_CATEGORY_NAME)
                    {
                        return Search::SwallowFacilitiesVendorPriority;
                    }
                    
                    if(result.GetCategory() == Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME)
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
                        int floorDistanceA = currentFloorIndex - a.GetFloor();
                        int floorDistanceB = currentFloorIndex - b.GetFloor();
                        
                        int absFloorDistanceA = abs(floorDistanceA);
                        int absFloorDistanceB = abs(floorDistanceB);
                        if(absFloorDistanceA == absFloorDistanceB)
                        {
                            return floorDistanceA > floorDistanceB;
                        }
                        
                        return absFloorDistanceA < absFloorDistanceB;
                    }
                    
                    return false;
                }
                
                bool GetOrderForWorkingGroups(const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
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
                
                bool hasMarkerForA = markerRepository.Contains(a.GetBuildingId());
                bool hasMarkerForB = markerRepository.Contains(b.GetBuildingId());
                
                if(!hasMarkerForA && !hasMarkerForB)
                {
                    return a.GetBuildingId().Value() < b.GetBuildingId().Value();
                }
                
                double distanceToA = std::numeric_limits<double>::max();
                double distanceToB = std::numeric_limits<double>::max();
                
                if(hasMarkerForA)
                {
                    Eegeo::dv3 buildingLocationEcef = markerRepository.Get(a.GetBuildingId()).GetMarkerLatLongAltitude().ToECEF();
                    distanceToA = (buildingLocationEcef - cameraFocusLocationEcef).LengthSq();
                }
                
                if(hasMarkerForB)
                {
                    Eegeo::dv3 buildingLocationEcef = markerRepository.Get(b.GetBuildingId()).GetMarkerLatLongAltitude().ToECEF();
                    distanceToB = (buildingLocationEcef - cameraFocusLocationEcef).LengthSq();
                }
                
                return distanceToA < distanceToB;
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
                    bool matchingCategory = a.GetCategory() == b.GetCategory() &&
                                            a.GetVendor() == Search::EegeoVendorName &&
                                            b.GetVendor() == Search::EegeoVendorName;
                    
                    if (matchingCategory)
                    {
                        if(a.GetCategory() == Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
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
                        else if(a.GetCategory() == Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME)
                        {
                            return GetOrderForWorkingGroups(a, b);
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