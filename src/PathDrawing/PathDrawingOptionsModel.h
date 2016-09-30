// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include "string"
#include "Types.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        class PathDrawingOptionsModel : protected Eegeo::NonCopyable
        {
        private:
            float m_routeWidth;
            float m_altitudeMeters;
            float m_routeSpeedMetersPerSecond;
            Eegeo::v4 m_routePrimaryColor;
            Eegeo::v4 m_routeSecondaryColor;
        
        public:
            PathDrawingOptionsModel();
            ~PathDrawingOptionsModel();
            
            void SetRouteWidth(float routeWidth);
            void SetRouteAltitudeMeter(float altitudeMeter);
            void SetRouteSpeed(float routeSpeedMeterPerSecond);
            void SetRoutePrimaryColor(Eegeo::v4 primaryColor);
            void SetRouteSecondaryColor(Eegeo::v4 secondaryColor);
            
            float GetRouteWidth();
            float GetRouteSpeed();
            float GetRouteAltitudeMeter();
            Eegeo::v4 GetRoutePrimaryColor();
            Eegeo::v4 GetRouteSecondaryColor();
            
        };
        
    }
}