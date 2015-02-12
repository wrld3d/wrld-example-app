// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInitialExperienceDialogsView.h"
#include "ICallback.h"
#include "InitialExperienceDialogType.h"
#include "CallbackCollection.h"
#include "AndroidNativeState.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			namespace View
			{
				class InitialExperienceDialogsView : public IInitialExperienceDialogsView
				{
				public:

					InitialExperienceDialogsView(AndroidNativeState& nativeState);
					~InitialExperienceDialogsView();

					void Open(const InitialExperienceDialogType::Values& dialogType, const std::string& title, const std::string &description);
					void Close();
					void CloseButtonTapped();
					void SetModalBackground(bool active);

					virtual void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);
					virtual void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);

				private:
					AndroidNativeState& m_nativeState;
					jclass m_uiViewClass;
					jobject m_uiView;

					Eegeo::Helpers::CallbackCollection0 m_closedButtonCallbacks;
				};
			}
		}
	}
}
