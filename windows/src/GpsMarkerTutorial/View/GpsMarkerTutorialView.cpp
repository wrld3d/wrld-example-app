// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "GpsMarkerTutorialView.h"
#include "ReflectionHelpers.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;
using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
	namespace GpsMarkerTutorial
	{
		namespace View
		{
			GpsMarkerTutorialView::GpsMarkerTutorialView()
			{
				m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.GpsMarkerTutorialView");
				ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
				m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

				mAnimateToActive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToActive");
				mAnimateToInactive.SetupMethod(m_uiViewClass, m_uiView, "AnimateToInactive");
				mUpdateScreenLocation.SetupMethod(m_uiViewClass, m_uiView, "UpdateScreenLocation");
			}

			GpsMarkerTutorialView::~GpsMarkerTutorialView()
			{
			}

			void GpsMarkerTutorialView::SetFullyOnScreen()
			{
				mAnimateToActive();
			}

			void GpsMarkerTutorialView::SetFullyOffScreen()
			{
				mAnimateToInactive();
			}

			void GpsMarkerTutorialView::UpdateScreenLocation(float x, float y)
			{
				mUpdateScreenLocation(x, y);
			}
		}
	}
}