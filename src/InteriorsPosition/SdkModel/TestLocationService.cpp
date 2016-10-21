// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "TestLocationService.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        namespace SdkModel
        {
            const bool TestLocationService::GetIsAuthorized() const
            {
                return true;
            }
            
            bool TestLocationService::IsIndoors()
            {
                return true;
            }
            
            bool TestLocationService::GetIndoorID(int& indoorID)
            {
                return true;
            }
            
            bool TestLocationService::GetLocation(Eegeo::Space::LatLong& latLong)
            {
                static int count = 0;
                ++count;
                
                latLong.SetLatitude(0.98541223610711293);
                latLong.SetLongitude(-0.051978828681127895);
                
                if(count > 360)
                {
                    count = 0;
                }
                else if(count > 240)
                {
                    latLong.SetLatitude(0.98541223610711293);
                    latLong.SetLongitude(-0.051982828681127895);
                }
                else if(count > 120)
                {
                    latLong.SetLatitude(0.98541223610711293);
                    latLong.SetLongitude(-0.051980828681127895);
                }
                return true;
            }
            
            bool TestLocationService::GetAltitude(double& altitude)
            {
                altitude = 31.69311;
                return true;
            }
            
            bool TestLocationService::GetFloorIndex(int& floorIndex)
            {
                floorIndex = 2;
                return true;
            }
            
            bool TestLocationService::GetHorizontalAccuracy(double& accuracy)
            {
                accuracy = 65;
                return true;
            }
            
            bool TestLocationService::GetHeadingDegrees(double& headingDegrees)
            {
                headingDegrees = 45;
                return true;
            }
            
            void TestLocationService::StopListening()
            {
            }
        }
    }
}