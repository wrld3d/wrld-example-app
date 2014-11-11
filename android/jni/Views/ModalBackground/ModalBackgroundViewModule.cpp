// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModalBackgroundViewModule.h"
#include "Modality.h"
#include "ModalBackgroundViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        ModalBackgroundViewModule::ModalBackgroundViewModule(
			AndroidNativeState& nativeState,
			Modality::IModalityModel& modalityModel
		)
        {
    		ASSERT_UI_THREAD

            m_pModalBackgroundViewController = Eegeo_NEW(ModalBackgroundViewController)(
				nativeState,
				modalityModel
            );
        }
        
        ModalBackgroundViewModule::~ModalBackgroundViewModule()
        {
        	ASSERT_UI_THREAD

            Eegeo_DELETE(m_pModalBackgroundViewController);
        }
        
        IModalBackgroundViewController& ModalBackgroundViewModule::GetModalBackgroundViewController() const
        {
        	ASSERT_UI_THREAD

            return *m_pModalBackgroundViewController;
        }
    }
}
