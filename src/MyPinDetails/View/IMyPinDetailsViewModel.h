// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "MyPins.h"

namespace ExampleApp
{
	namespace MyPinDetails
	{
		class IMyPinDetailsViewModel
		{
		public:
			virtual ~IMyPinDetailsViewModel() { }

            virtual const MyPins::MyPinModel& GetMyPinModel() const = 0;

			virtual bool TryAcquireReactorControl() = 0;

			virtual bool IsOpen() const = 0;

            virtual void Open(const MyPins::MyPinModel& myPinModel) = 0;

			virtual void Close() = 0;

			virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

			virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

			virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

			virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
		};
	}
}
