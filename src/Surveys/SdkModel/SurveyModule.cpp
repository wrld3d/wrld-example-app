// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SurveyModule.h"

#include "SurveyObserver.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace SdkModel
        {
            SurveyModule::SurveyModule(ExampleAppMessaging::TMessageBus& messageBus,
                                       PersistentSettings::IPersistentSettingsModel& persistentSettingsModel)
            : m_pSurveyObserver(NULL)
            {
                m_pSurveyObserver = Eegeo_NEW(SurveyObserver)(messageBus,
                                                              persistentSettingsModel);
            }
            
            SurveyModule::~SurveyModule()
            {
                Eegeo_DELETE m_pSurveyObserver;
            }
            
            SurveyObserver& SurveyModule::GetSurveyObserver() const
            {
                return *m_pSurveyObserver;
            }
        }
    }
}
