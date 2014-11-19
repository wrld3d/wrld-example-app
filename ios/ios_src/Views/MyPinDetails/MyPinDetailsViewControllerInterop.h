// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsViewController.h"
#include "Types.h"
#include "MyPinDetailsView.h"
#include "IMyPinDetailsViewModel.h"
#include "ICallback.h"

@class MyPinDetailsViewController;

namespace ExampleApp
{
	namespace MyPinDetails
	{
		class MyPinDetailsViewControllerInterop : private Eegeo::NonCopyable
		{
			MyPinDetailsViewController* m_pInstance;
			MyPinDetails::IMyPinDetailsViewModel& m_MyPinDetailsViewModel;

			Eegeo::Helpers::ICallback0* m_pMyPinDetailsOpenedCallback;
			Eegeo::Helpers::ICallback0* m_pMyPinDetailsClosedCallback;

			void MyPinDetailsOpenedCallback()
			{
				[m_pInstance openWithModel:m_MyPinDetailsViewModel.GetMyPinModel()];
			}

			void MyPinDetailsClosedCallback()
			{
				[m_pInstance close];
			}

		public:
			MyPinDetailsViewControllerInterop(MyPinDetailsViewController* pInstance,
			                                     IMyPinDetailsViewModel& MyPinDetailsViewModel)
				: m_pInstance(pInstance)
				, m_MyPinDetailsViewModel(MyPinDetailsViewModel)
				, m_pMyPinDetailsOpenedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<MyPinDetailsViewControllerInterop>)(this, &MyPinDetailsViewControllerInterop::MyPinDetailsOpenedCallback))
				, m_pMyPinDetailsClosedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<MyPinDetailsViewControllerInterop>)(this, &MyPinDetailsViewControllerInterop::MyPinDetailsClosedCallback))
			{
				m_MyPinDetailsViewModel.InsertOpenedCallback(*m_pMyPinDetailsOpenedCallback);
				m_MyPinDetailsViewModel.InsertClosedCallback(*m_pMyPinDetailsClosedCallback);
			}

			~MyPinDetailsViewControllerInterop()
			{

				m_MyPinDetailsViewModel.RemoveOpenedCallback(*m_pMyPinDetailsOpenedCallback);
				m_MyPinDetailsViewModel.RemoveClosedCallback(*m_pMyPinDetailsClosedCallback);

				Eegeo_DELETE m_pMyPinDetailsOpenedCallback;
				Eegeo_DELETE m_pMyPinDetailsClosedCallback;
			}
		};
	}
}
