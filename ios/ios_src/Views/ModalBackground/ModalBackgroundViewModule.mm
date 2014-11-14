// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModalBackgroundViewModule.h"
#include "IModalityModel.h"
#include "ModalBackgroundViewController.h"

namespace ExampleApp
{
	namespace ModalBackground
	{
		ModalBackgroundViewModule::ModalBackgroundViewModule(Modality::IModalityModel& modalityModel)
		{
			m_pModalBackgroundViewController = [[ModalBackgroundViewController alloc] initWithParams :&modalityModel];
		}

		ModalBackgroundViewModule::~ModalBackgroundViewModule()
		{
			[m_pModalBackgroundViewController release];
		}

		ModalBackgroundViewController& ModalBackgroundViewModule::GetModalBackgroundViewController() const
		{
			return *m_pModalBackgroundViewController;
		}

		ModalBackgroundView& ModalBackgroundViewModule::GetModalBackgroundView() const
		{
			return *[m_pModalBackgroundViewController pModalBackgroundView];
		}
	}
}
