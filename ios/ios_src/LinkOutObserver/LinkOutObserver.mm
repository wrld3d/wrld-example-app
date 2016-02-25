// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LinkOutObserver.h"

#include <sstream>

#include "IMetricsService.h"
#include "IPersistentSettingsModel.h"

namespace
{
    const std::string ExitSettingName = "ExitViaDeepLink";
    const std::string TimeSettingName = "DeepLinkExitTime";

    const std::string ResumeMetricName = "DeepLinkResume";
    const std::string ResumeMetricDelayKey = "ResumeDelay";

    const std::string ExitMetricName = "DeepLinkExit";
    const std::string ExitMetricHostKey = "Host";
    
    const double MaxResumeTime = 300.0;
}

namespace ExampleApp
{
    namespace LinkOutObserver
    {
        LinkOutObserver::LinkOutObserver(Metrics::IMetricsService& metricsService,
                                         PersistentSettings::IPersistentSettingsModel& persistentSettingsModel)
        : m_metricsService(metricsService)
        , m_persistentSettingsModel(persistentSettingsModel)
        {
            
        }
            
        LinkOutObserver::~LinkOutObserver()
        {
            
        }
        
        void LinkOutObserver::CheckResumeFromLink() const
        {
            bool lastExitViaDeepLink = false;
            if(m_persistentSettingsModel.TryGetValue(ExitSettingName, lastExitViaDeepLink) && lastExitViaDeepLink)
            {
                m_persistentSettingsModel.SetValue(ExitSettingName, false);
                
                double lastExitTime;
                
                if(m_persistentSettingsModel.TryGetValue(TimeSettingName, lastExitTime))
                {
                    double currentTime = CFAbsoluteTimeGetCurrent();
                    
                    if(currentTime - lastExitTime <= MaxResumeTime)
                    {
                        std::stringstream timeDifference;
                        timeDifference << (currentTime - lastExitTime);
                        
                        m_metricsService.SetEvent(ResumeMetricName, ResumeMetricDelayKey, timeDifference.str());
                    }
                }
            }
        }
        
        void LinkOutObserver::OnAppStart() const
        {
            CheckResumeFromLink();
        }
            
        void LinkOutObserver::OnAppResume() const
        {
            CheckResumeFromLink();
        }
            
        void LinkOutObserver::OnLinkOut(const std::string& linkHost) const
        {
            m_metricsService.SetEvent(ExitMetricName, ExitMetricHostKey, linkHost);
            
            m_persistentSettingsModel.SetValue(ExitSettingName, true);
            m_persistentSettingsModel.SetValue(TimeSettingName, CFAbsoluteTimeGetCurrent());
        }
    }
}