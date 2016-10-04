// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "VectorMath.h"
#include "RenderCamera.h"

namespace ExampleApp
{
	namespace Helpers
	{
		namespace ScaleHelpers
		{
			float ComputeModelScaleForScreenWithPixelScaling(const Eegeo::Camera::RenderCamera& renderCamera,
                                                             const Eegeo::dv3& objectEcefPosition,
                                                             float pixelScale,
                                                             float oversampleScale);
		}
	}
}