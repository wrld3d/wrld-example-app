// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkLocationHandler.h"
#include <vector>
#include "StringHelpers.h"
#include "LatLongAltitude.h"
#include "ICameraTransitionController.h"
#include "InteriorId.h"

namespace
{
    double DEFAULT_DISTANCE = 1000;
    double DEFAULT_HEADING = 0;
    std::string DEFAULT_INDOOR_ID = "";
    int DEFAULT_FLOOR_INDEX = 0;
    
    //Empty string at 0 index as path of /lat/long[/distance/heading]
    const size_t LAT_INDEX = 1;
    const size_t LONG_INDEX = 2;
    const size_t DISTANCE_INDEX = 3;
    const size_t HEADING_INDEX = 4;
    const size_t INDOOR_INDEX = 5;
    const size_t FLOOR_INDEX = 6;
}

namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            DeepLinkLocationHandler::DeepLinkLocationHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController, Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory)
            : m_cameraTransitionController(cameraTransitionController)
            , m_alertBoxFactory(alertBoxFactory)
            ,m_failAlertHandler(this, &DeepLinkLocationHandler::OnFailAlertBoxDismissed)
            {
            }

            void DeepLinkLocationHandler::HandleDeepLink(const AppInterface::UrlData& data)
            {
                std::vector<std::string> parts;
                size_t numParts = Eegeo::Helpers::Split(data.path, '/', parts);
                Eegeo::Space::LatLong latLon(0, 0);
                
                if(numParts > LONG_INDEX && Eegeo::Helpers::TryParseLatLong(parts.at(LAT_INDEX), parts.at(LONG_INDEX), latLon))
                {
                    double distance = DEFAULT_DISTANCE;
                    if(numParts > DISTANCE_INDEX)
                    {
                        if(!Eegeo::Helpers::TryParseDouble(parts.at(DISTANCE_INDEX), distance))
                        {
                            m_alertBoxFactory.CreateSingleOptionAlertBox("Invalid distance in deep link: "+parts.at(HEADING_INDEX), URL_FORMAT_MESSAGE, m_failAlertHandler);
                        }
                    }
                    
                    double heading = DEFAULT_HEADING;
                    if(numParts > HEADING_INDEX)
                    {
                        if(!Eegeo::Helpers::TryParseDouble(parts.at(HEADING_INDEX), heading))
                        {
                            m_alertBoxFactory.CreateSingleOptionAlertBox("Invalid bearing in deep link: "+parts.at(4), URL_FORMAT_MESSAGE, m_failAlertHandler);
                        }
                    }
                    
                    std::string indoorId = DEFAULT_INDOOR_ID;
                    if(numParts > INDOOR_INDEX)
                    {
                        indoorId = parts.at(INDOOR_INDEX);
                    }
                    Eegeo::Resources::Interiors::InteriorId interiorId(indoorId);
                    
                    int floorIndex = DEFAULT_FLOOR_INDEX;
                    if(numParts > FLOOR_INDEX)
                    {
                        if(!Eegeo::Helpers::TryParseInt(parts.at(FLOOR_INDEX), floorIndex))
                        {
                            m_alertBoxFactory.CreateSingleOptionAlertBox("Invalid floor index in deep link: " + parts.at(FLOOR_INDEX), URL_FORMAT_MESSAGE, m_failAlertHandler);
                        }
                    }
                    
                    if(interiorId.IsValid())
                    {
                        Eegeo_TTY("lat=%f lon=%f, distance=%f, heading=%f, indoorId=%s, floorIndex=%d", latLon.GetLatitudeInDegrees(), latLon.GetLongitudeInDegrees(), distance, heading, interiorId.Value().c_str(), floorIndex);
                        bool jumpIfFar = true;
                        bool setGpsModeOff = true;
                        bool setInteriorHeading = true;
                        m_cameraTransitionController.StartTransitionTo(latLon.ToECEF(), (float) distance, (float) Eegeo::Math::Deg2Rad(heading), interiorId, floorIndex, jumpIfFar, setGpsModeOff, setInteriorHeading);
                    }
                    else
                    {
                        Eegeo_TTY("lat=%f lon=%f, distance=%f, heading=%f", latLon.GetLatitudeInDegrees(), latLon.GetLongitudeInDegrees(), distance, heading);
                        m_cameraTransitionController.StartTransitionTo(latLon.ToECEF(), (float) distance, (float) Eegeo::Math::Deg2Rad(heading));
                    }
                }
                else
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("Incorrect location deeplink URL format: "+std::string(data.path), URL_FORMAT_MESSAGE, m_failAlertHandler);
                }
            }

            void DeepLinkLocationHandler::OnFailAlertBoxDismissed()
            { //Do nothing
            }
        }
    }
}
