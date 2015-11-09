// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ImagePathHelpers.h"
#include "WindowsImagePathHelpers.h"
#include "Logger.h"

namespace
{
    // As defined at http://developer.android.com/reference/android/util/DisplayMetrics.html
    const int DensityLow 		= 120;
    const int DensityMedium 	= 160;
    const int DensityTV 		= 213;
    const int DensityHigh 		= 240;
    const int DensityXHigh 		= 320;
    const int DensityXXHigh		= 480;
    const int DensityXXXHigh 	= 640;

    std::string g_densitySuffix = "";
    float g_pixelScale;
}

namespace ExampleApp
{
    namespace Helpers
    {
        namespace ImageHelpers
        {
            void SetDeviceDensity(int density)
            {
                // Some devices feature intermediate densities. Downscale these appropriately.
                if(density > DensityXHigh && density < DensityXXHigh)
                {
                    density = DensityXHigh;
                }

                if(density > DensityXXHigh && density < DensityXXXHigh)
                {
                    density = DensityXXHigh;
                }

                switch(density)
                {
                    case DensityLow: 		{ g_densitySuffix = "@0.75x"; g_pixelScale = 0.75f; } break;
                    case DensityMedium: 	{ g_densitySuffix = ""; g_pixelScale = 1.0f; } break;
                    case DensityTV: 		{ g_densitySuffix = "@1.5x"; g_pixelScale = 1.5f; } break;
                    case DensityHigh: 		{ g_densitySuffix = "@1.5x"; g_pixelScale = 1.5f;} break;
                    case DensityXHigh: 		{ g_densitySuffix = "@2x"; g_pixelScale = 2.0f; } break;
                    case DensityXXHigh: 	{ g_densitySuffix = "@3x"; g_pixelScale = 3.0f; } break;
                    case DensityXXXHigh: 	{ g_densitySuffix = "@3x"; g_pixelScale = 3.0f; } break;
                }


            }

            std::string GetImageNameForDevice(const std::string& name,
                                              const std::string& ext)
            {
                return name + g_densitySuffix + ext;
            }

            float GetPixelScale()
            {
                return g_pixelScale;
            }
        }
    }
}
