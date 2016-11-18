// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkLocationHandler.h"
#include <vector>
#include "StringHelpers.h"
#include "LatLongAltitude.h"
#include "ICameraTransitionController.h"

namespace
{
    double DEFAULT_DISTANCE = 1000;
    double DEFAULT_HEADING = 0;
    
    //Empty string at 0 index as path of /lat/long[/distance/heading]
    const size_t LAT_INDEX = 1;
    const size_t LONG_INDEX = 2;
    const size_t DISTANCE_INDEX = 3;
    const size_t HEADING_INDEX = 4;
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
                        if(!Eegeo::Helpers::TryParseDouble(parts.at(DISTANCE_INDEX), DEFAULT_DISTANCE))
                        {
                            m_alertBoxFactory.CreateSingleOptionAlertBox("Invalid distance in deep link: "+parts.at(HEADING_INDEX), URL_FORMAT_MESSAGE, m_failAlertHandler);
                        }
                    }
                    
                    double heading = DEFAULT_HEADING;
                    if(numParts > HEADING_INDEX)
                    {
                        if(!Eegeo::Helpers::TryParseDouble(parts.at(4), heading))
                        {
                            m_alertBoxFactory.CreateSingleOptionAlertBox("Invalid bearing in deep link: "+parts.at(4), URL_FORMAT_MESSAGE, m_failAlertHandler);
                        }
                    }
                    
                    Eegeo_TTY("lat=%f lon=%f, distance=%f, heading=%f", latLon.GetLatitudeInDegrees(), latLon.GetLongitudeInDegrees(), distance, heading);
                    m_cameraTransitionController.StartTransitionTo(latLon.ToECEF(), (float) distance, (float) Eegeo::Math::Deg2Rad(heading));
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
