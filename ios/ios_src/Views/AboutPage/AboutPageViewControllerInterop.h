// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AboutPageViewController.h"
#include "Types.h"
#include "AboutPageView.h"
#include "IAboutPageViewModel.h"
#include "ICallback.h"

@class AboutPageViewController;

namespace ExampleApp
{
    namespace AboutPage
    {
        class AboutPageViewControllerInterop : private Eegeo::NonCopyable
        {
            AboutPageViewController* m_pInstance;
            AboutPage::IAboutPageViewModel& m_aboutPageViewModel;
            
            Eegeo::Helpers::ICallback0* m_pAboutPageOpenedCallback;
            Eegeo::Helpers::ICallback0* m_pAboutPageClosedCallback;
            
            void AboutPageOpenedCallback()
            {
                [m_pInstance open];
            }
            
            void AboutPageClosedCallback()
            {
                [m_pInstance close];
            }
            
        public:
            AboutPageViewControllerInterop(AboutPageViewController* pInstance,
                                           IAboutPageViewModel& aboutPageViewModel)
            : m_pInstance(pInstance)
            , m_aboutPageViewModel(aboutPageViewModel)
            , m_pAboutPageOpenedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<AboutPageViewControllerInterop>(this, &AboutPageViewControllerInterop::AboutPageOpenedCallback)))
            , m_pAboutPageClosedCallback(Eegeo_NEW(Eegeo::Helpers::TCallback0<AboutPageViewControllerInterop>(this, &AboutPageViewControllerInterop::AboutPageClosedCallback)))
            {
                m_aboutPageViewModel.InsertOpenedCallback(*m_pAboutPageOpenedCallback);
                m_aboutPageViewModel.InsertClosedCallback(*m_pAboutPageClosedCallback);
            }
            
            ~AboutPageViewControllerInterop()
            {
                
                m_aboutPageViewModel.RemoveOpenedCallback(*m_pAboutPageOpenedCallback);
                m_aboutPageViewModel.RemoveClosedCallback(*m_pAboutPageClosedCallback);
                
                Eegeo_DELETE m_pAboutPageOpenedCallback;
                Eegeo_DELETE m_pAboutPageClosedCallback;
            }
        };
    }
}
