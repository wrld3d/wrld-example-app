// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "ReflectionHelpers.h"

namespace ExampleApp
{
	namespace GpsMarkerTutorial
	{
		namespace View
		{
			class GpsMarkerTutorialView
			{
			private:
				gcroot<System::Type^> m_uiViewClass;
				gcroot<System::Object^> m_uiView;

				Helpers::ReflectionHelpers::Method<void> mAnimateToActive;
				Helpers::ReflectionHelpers::Method<void> mAnimateToInactive;
				Helpers::ReflectionHelpers::Method<float, float> mUpdateScreenLocation;

			public:
				GpsMarkerTutorialView();
				~GpsMarkerTutorialView();

				void SetFullyOnScreen();
				void SetFullyOffScreen();
				bool IsOnScreen();

				void UpdateScreenLocation(float x, float y);
			};
		}
	}
}