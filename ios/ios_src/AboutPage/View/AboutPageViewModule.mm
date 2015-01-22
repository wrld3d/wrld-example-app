// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageViewModule.h"
#include "IAboutPageViewModel.h"
#include "AboutPageView.h"
#include "AboutPageController.h"
#include "AboutPageViewInterop.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            AboutPageViewModule::AboutPageViewModule(IAboutPageViewModel& aboutPageViewModel)
            {
                m_pView = [[AboutPageView alloc] initView];
                m_pController = Eegeo_NEW(AboutPageController)(*[m_pView getInterop], aboutPageViewModel);
            }

            AboutPageViewModule::~AboutPageViewModule()
            {
                Eegeo_DELETE m_pController;
                [m_pView release];
            }

            AboutPageController& AboutPageViewModule::GetAboutPageController() const
            {
                return *m_pController;
            }

            AboutPageView& AboutPageViewModule::GetAboutPageView() const
            {
                return *m_pView;
            }
        }
    }
}
