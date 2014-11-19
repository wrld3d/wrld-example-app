// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsViewModel.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
	namespace MyPinDetails
	{
		MyPinDetailsViewModel::MyPinDetailsViewModel(Eegeo::Helpers::TIdentity identity,
                                                     Reaction::IReactionControllerModel& reactionControllerModel)
        : m_openable(identity, reactionControllerModel)
		{

		}

		MyPinDetailsViewModel::~MyPinDetailsViewModel()
		{

		}

		bool MyPinDetailsViewModel::TryAcquireReactorControl()
		{
			return m_openable.TryAcquireReactorControl();
		}

        const MyPins::MyPinModel& MyPinDetailsViewModel::GetMyPinModel() const
		{
			Eegeo_ASSERT(IsOpen(), "Cannot read SearchResultModel when view model is not open.\n");
			return m_myPinModel;
		}

		bool MyPinDetailsViewModel::IsOpen() const
		{
			return m_openable.IsFullyOpen();
		}

        void MyPinDetailsViewModel::Open(const MyPins::MyPinModel& myPinModel)
		{
			Eegeo_ASSERT(!IsOpen(), "Cannot open MyPinDetailsViewModel when already open.\n");
			if(m_openable.Open())
			{
				m_myPinModel = myPinModel;
				m_openedCallbacks.ExecuteCallbacks();
			}
		}

		void MyPinDetailsViewModel::Close()
		{
			Eegeo_ASSERT(IsOpen(), "Cannot close SearchResultModel when view model when already closed.\n");

			{
				const bool closed = m_openable.Close();
				Eegeo_ASSERT(closed, "Failed to close");
			}

			m_closedCallbacks.ExecuteCallbacks();
		}

		OpenableControlViewModel::IOpenableControlViewModel& MyPinDetailsViewModel::GetOpenableControl()
		{
			return m_openable;
		}

		void MyPinDetailsViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
		{
			m_openedCallbacks.AddCallback(openedCallback);
		}

		void MyPinDetailsViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
		{
			m_openedCallbacks.RemoveCallback(openedCallback);
		}

		void MyPinDetailsViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
		{
			m_closedCallbacks.AddCallback(closedCallback);
		}

		void MyPinDetailsViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
		{
			m_closedCallbacks.RemoveCallback(closedCallback);
		}
	}
}
