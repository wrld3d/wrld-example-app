// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ImagePathHelpers.h"
#include "AndroidImagePathHelpers.h"
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
}

namespace ExampleApp
{
    namespace Helpers
    {
        namespace ImageHelpers
        {
    		void SetDeviceDensity(int density)
    		{
    			switch(density)
    			{
					case DensityLow: 		{ g_densitySuffix = "@0.75x"; } break;
					case DensityMedium: 	{ g_densitySuffix = ""; } break;
					case DensityTV: 		{ g_densitySuffix = "@1.5x"; } break;
					case DensityHigh: 		{ g_densitySuffix = "@1.5x"; } break;
					case DensityXHigh: 		{ g_densitySuffix = "@2x"; } break;
					case DensityXXHigh: 	{ g_densitySuffix = "@3x"; } break;
					case DensityXXXHigh: 	{ g_densitySuffix = "@3x"; } break;
    			}
    		}

            std::string GetImageNameForDevice(const std::string& name,
                                              const std::string& ext)
            {
            	return name + g_densitySuffix + ext;
            }
        }
    }
}
