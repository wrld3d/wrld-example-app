// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PathDrawingOptionsModel.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        
        PathDrawingOptionsModel::PathDrawingOptionsModel()
        : m_routeWidth(4.0f)
        , m_altitudeMeters(1.0f)
        , m_routeSpeedMetersPerSecond(40.0f)
        , m_routePrimaryColor(1, 0.62f, 0, 1)
        , m_routeSecondaryColor(1, 1, 1, 1)
        {
        
        }
        
        PathDrawingOptionsModel::~PathDrawingOptionsModel()
        {
            
        }
        
        void PathDrawingOptionsModel::SetRouteWidth(float routeWidth)
        {
            m_routeWidth = routeWidth;
        }
        
        void PathDrawingOptionsModel::SetRouteAltitudeMeter(float altitudeMeter)
        {
            m_altitudeMeters = altitudeMeter;
        }

        void PathDrawingOptionsModel::SetRouteSpeed(float routeSpeedMeterPerSecond)
        {
            m_routeSpeedMetersPerSecond = routeSpeedMeterPerSecond;
        }
        
        void PathDrawingOptionsModel::SetRoutePrimaryColor(Eegeo::v4 primaryColor)
        {
            m_routePrimaryColor = primaryColor;
        }
        
        void PathDrawingOptionsModel::SetRouteSecondaryColor(Eegeo::v4 secondaryColor)
        {
            m_routeSecondaryColor = secondaryColor;
        }
        
        float PathDrawingOptionsModel::GetRouteWidth()
        {
            return m_routeWidth;
        }
        
        float PathDrawingOptionsModel::GetRouteSpeed()
        {
            return m_routeSpeedMetersPerSecond;
        }
        
        float PathDrawingOptionsModel::GetRouteAltitudeMeter()
        {
            return m_altitudeMeters;
        }
        
        Eegeo::v4 PathDrawingOptionsModel::GetRoutePrimaryColor()
        {
            return m_routePrimaryColor;
        }
        
        Eegeo::v4 PathDrawingOptionsModel::GetRouteSecondaryColor()
        {
            return m_routeSecondaryColor;
        }
        
    }
}