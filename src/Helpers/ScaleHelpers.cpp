// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "ScaleHelpers.h"
#include "TransformHelpers.h"

namespace ExampleApp
{
	namespace Helpers
	{
		namespace ScaleHelpers
		{
			float ComputeModelScaleForScreenWithPixelScaling(const Eegeo::Camera::RenderCamera& renderCamera,
                                                             const Eegeo::dv3& objectEcefPosition,
                                                             float pixelScale,
                                                             float oversampleScale)
			{
				const float scaleModifier = ((pixelScale * oversampleScale * 2) / renderCamera.GetViewportHeight());
				const float scaleForPoint = Eegeo::Helpers::TransformHelpers::ComputeModelScaleForConstantScreenSizeWithVerticalFoV(renderCamera, objectEcefPosition);
				return scaleModifier * scaleForPoint;
			}
		}
	}
}