// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ModalBackgroundViewModule.h"
#include "IModalityModel.h"
#include "ModalBackgroundView.h"
#include "ModalBackgroundController.h"
#include "IModalBackgroundView.h"
#include "ModalBackgroundViewInterop.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace ModalBackground
    {
        namespace View
        {
            ModalBackgroundViewModule::ModalBackgroundViewModule(Modality::View::IModalityModel& modalityModel, const Eegeo::Rendering::ScreenProperties& screenProperties)
            {
                m_pView = [[ModalBackgroundView alloc] initWithParams:screenProperties.GetScreenWidth() :screenProperties.GetScreenHeight()];
                m_pController = Eegeo_NEW(Modality::View::ModalBackgroundController)(*[m_pView getInterop], modalityModel);
            }

            ModalBackgroundViewModule::~ModalBackgroundViewModule()
            {
                Eegeo_DELETE m_pController;
                [m_pView release];
            }
            
            Modality::View::IModalBackgroundView& ModalBackgroundViewModule::GetModalBackgroundViewInterop()
            {
                return *[m_pView getInterop];
            }

            ModalBackgroundView& ModalBackgroundViewModule::GetModalBackgroundView()
            {
                return *m_pView;
            }
        }
    }
}
