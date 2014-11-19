// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IMyPinDetailsViewModel.h"
#include "MyPinModel.h"
#include "CallbackCollection.h"
#include "MyPinDetailsOpenableControl.h"
#include "Reaction.h"

namespace ExampleApp
{
	namespace MyPinDetails
	{
		class MyPinDetailsViewModel : public IMyPinDetailsViewModel, private Eegeo::NonCopyable
		{
			MyPins::MyPinModel m_myPinModel;
			Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
			Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
			MyPinDetailsOpenableControl m_openable;

		public:
			MyPinDetailsViewModel(Eegeo::Helpers::TIdentity identity,
			                         Reaction::IReactionControllerModel& reactionControllerModel);

			~MyPinDetailsViewModel();

            const MyPins::MyPinModel& GetMyPinModel() const;

			bool TryAcquireReactorControl();

			bool IsOpen() const;

            void Open(const MyPins::MyPinModel& myPinModel);

			void Close();

			OpenableControlViewModel::IOpenableControlViewModel& GetOpenableControl();

			void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);

			void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);

			void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);

			void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
		};
	}
}
