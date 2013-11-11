#include "DebugPrimitiveRenderingExample.h"
#include "DebugPrimitiveRenderer.h"
#include "LatLongAltitude.h"
#include "CoordinateConversion.h"


namespace Examples
{
    void DebugPrimitiveRenderingExample::Start()
    {
        
    }

    void DebugPrimitiveRenderingExample::Update()
    {
        
    }

    void DebugPrimitiveRenderingExample::Draw()
    {
        Eegeo::dv3 ecefA = ConvertLatLongAltitudeToEcef(Eegeo::Space::LatLongAltitude::FromDegrees(37.785063, -122.403436, 10));
        Eegeo::dv3 ecefB = ConvertLatLongAltitudeToEcef(Eegeo::Space::LatLongAltitude::FromDegrees(37.78469,-122.40143, 100));
        
        Eegeo::dv3 colour(1.0f, 0.0f, 1.0f);
        float alpha = 0.8f;
        float lineWidth = 10.0f;
        
        m_debugPrimitiveRenderer.DrawEcefLine(ecefA,
                                              ecefB,
                                              Eegeo::v4(colour.GetX(), colour.GetY(), colour.GetZ(), alpha),
                                              lineWidth);
        }

    void DebugPrimitiveRenderingExample::Suspend()
    {
        
    }
}