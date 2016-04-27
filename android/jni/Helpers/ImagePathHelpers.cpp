// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ImagePathHelpers.h"
#include "AndroidImagePathHelpers.h"
#include "Logger.h"

#include <vector>
#include <algorithm>

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

	struct DensityPredicate
	{
		DensityPredicate(int sourceDensity) : m_sourceDensity(sourceDensity){}
		bool operator()(const int& lhs, const int& rhs)
		{
			return std::abs(lhs - m_sourceDensity) < std::abs(rhs - m_sourceDensity);
		}
	private:
		int m_sourceDensity;
	};

	int ToNearestDensity(float density)
	{
		int densityArray[] = { DensityLow, DensityMedium, DensityTV, DensityHigh, DensityXHigh, DensityXXHigh, DensityXXXHigh };
		std::vector<int> densities(densityArray, densityArray + 7);

		return *std::min_element(densities.begin(), densities.end(), DensityPredicate(density));
	}
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

    			// IH - On Android N, users can switch the density manually.
    			//      I'm seeing a density value not listed in the above DisplayMetrics link.
    			//      Get nearest density possible from our expected density values
    			density = ToNearestDensity(density);

    			switch(density)
    			{
					case DensityLow: 		{ g_densitySuffix = "@0.75x"; g_pixelScale = 0.75f; } break;
					case DensityMedium: 	{ g_densitySuffix = ""; g_pixelScale = 1.0f; } break;
					case DensityTV: 		{ g_densitySuffix = "@1.5x"; g_pixelScale = 1.5f; } break;
					case DensityHigh: 		{ g_densitySuffix = "@1.5x"; g_pixelScale = 1.5f;} break;
					case DensityXHigh: 		{ g_densitySuffix = "@2x"; g_pixelScale = 2.0f; } break;
					case DensityXXHigh: 	{ g_densitySuffix = "@3x"; g_pixelScale = 3.0f; } break;
					case DensityXXXHigh: 	{ g_densitySuffix = "@3x"; g_pixelScale = 3.0f; } break;
					default: 			    { Eegeo_ASSERT(false, "ImageHelpers :: Unknown density value found"); } break;
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
