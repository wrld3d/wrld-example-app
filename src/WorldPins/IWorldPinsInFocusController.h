// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VectorMathDecl.h"
#include "Camera.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class IWorldPinsInFocusController
		{
		public:
			virtual ~IWorldPinsInFocusController() { }

            virtual void Update(float dt, const Eegeo::dv3& ecefInterestPoint, const Eegeo::Camera::RenderCamera& renderCamera) = 0;
		};
	}
}
