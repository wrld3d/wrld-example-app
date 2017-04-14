// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SurveyObserver.h"

#include <string>

#include "IPersistentSettingsModel.h"
#include "StartUxSurveyMessage.h"
#include "TimeHelpers.h"

namespace
{
    const std::string SurveyConditionsKeyName = "SurveyConditions";
    const std::string SurveyOfferedKeyName = "SurveyOffered";
    
    const unsigned int StartUpRequirementCount = 3;
    
    enum SurveyConditionFlags
    {
        StartUpCountMask = 0x03,
        SearchPerformed = 0x04,
        SearchResultSelected = 0x08,
        WeatherSelected = 0x10,
        PinCreated = 0x20,
        TimeSpent = 0x40
    };
}

namespace ExampleApp
{
    namespace Surveys
    {
        namespace SdkModel
        {
            SurveyObserver::SurveyObserver(ExampleAppMessaging::TMessageBus& messageBus,
                                           PersistentSettings::IPersistentSettingsModel& persistentSettingsModel)
            : m_messageBus(messageBus)
            , m_persistentSettingsModel(persistentSettingsModel)
            , m_onSearchPerformedMessage(this, &SurveyObserver::OnSearchPerformedMessage)
            , m_onTagSearchPerformedMessage(this, &SurveyObserver::OnTagSearchPerformedMessage)
            , m_onSearchResultSelected(this, &SurveyObserver::OnSearchResultSelected)
            , m_onWeatherSelected(this, &SurveyObserver::OnWeatherSelected)
            , m_onPinCreated(this, &SurveyObserver::OnPinCreated)
            , m_onSurveyTimeRequirementMet(this, &SurveyObserver::OnTimeSpentInApp)
            {
                m_messageBus.SubscribeNative(m_onSearchPerformedMessage);
                m_messageBus.SubscribeNative(m_onTagSearchPerformedMessage);
                m_messageBus.SubscribeNative(m_onSearchResultSelected);
                m_messageBus.SubscribeNative(m_onWeatherSelected);
                m_messageBus.SubscribeNative(m_onPinCreated);
                m_messageBus.SubscribeNative(m_onSurveyTimeRequirementMet);
                
            }
            
            SurveyObserver::~SurveyObserver()
            {
                m_messageBus.UnsubscribeNative(m_onSurveyTimeRequirementMet);
                m_messageBus.UnsubscribeNative(m_onSearchPerformedMessage);
                m_messageBus.UnsubscribeNative(m_onTagSearchPerformedMessage);
                m_messageBus.UnsubscribeNative(m_onSearchResultSelected);
                m_messageBus.UnsubscribeNative(m_onWeatherSelected);
                m_messageBus.UnsubscribeNative(m_onPinCreated);
            }
            
            void SurveyObserver::OnStartup()
            {
                if(SurveyOffered())
                {
                    return;
                }
                
                unsigned int surveyConditions = GetSurveyConditions();
                
                unsigned int startUpCount = surveyConditions & StartUpCountMask;
                
                if(startUpCount < StartUpRequirementCount)
                {
                    ++ startUpCount;
                    SetSurveyConditions((surveyConditions & ~(StartUpCountMask)) | startUpCount);
                }
            }
            
            void SurveyObserver::OnSearchPerformedMessage(const SearchMenu::SearchMenuPerformedSearchMessage& message)
            {
                if(SurveyOffered())
                {
                    return;
                }
                
                SetSurveyConditionsFlag(SearchPerformed);
            }
            
            void SurveyObserver::OnTagSearchPerformedMessage(const TagSearch::TagSearchSelectedMessage& message)
            {
                if(SurveyOffered())
                {
                    return;
                }
                
                SetSurveyConditionsFlag(SearchPerformed);
            }
            
            void SurveyObserver::OnSearchResultSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message)
            {
                if(SurveyOffered())
                {
                    return;
                }
                
                SetSurveyConditionsFlag(SearchResultSelected);
            }
            
            void SurveyObserver::OnWeatherSelected(const WeatherMenu::WeatherSelectedMessage& message)
            {
                if(SurveyOffered())
                {
                    return;
                }
                
                SetSurveyConditionsFlag(WeatherSelected);
            }
            
            void SurveyObserver::OnPinCreated(const MyPinCreation::MyPinCreationViewSavePinMessage& message)
            {
                if(SurveyOffered())
                {
                    return;
                }
                
                SetSurveyConditionsFlag(PinCreated);
            }
            
            void SurveyObserver::OnTimeSpentInApp(const SurveyTimeRequirementMetMessage& message)
            {
                if(SurveyOffered() || !StartUpRequirementsMet())
                {
                    return;
                }

                SetSurveyConditionsFlag(TimeSpent);
            }
            
            bool SurveyObserver::SurveyOffered()
            {
                bool surveyOffered = false;
                
                m_persistentSettingsModel.TryGetValue(SurveyOfferedKeyName, surveyOffered);
                
                return surveyOffered;
            }
            
            unsigned int SurveyObserver::GetSurveyConditions() const
            {
                int surveyConditions = 0;
                
                m_persistentSettingsModel.TryGetValue(SurveyConditionsKeyName, surveyConditions);
                
                return static_cast<unsigned int>(surveyConditions);
            }
            
            void SurveyObserver::SetSurveyConditions(unsigned int surveyConditions)
            {
                m_persistentSettingsModel.SetValue(SurveyConditionsKeyName, static_cast<int>(surveyConditions));
                
                CheckRequirementsMet();
            }
            
            void SurveyObserver::SetSurveyConditionsFlag(unsigned int conditionFlag)
            {
                SetSurveyConditions(GetSurveyConditions() | conditionFlag);
            }
            
            void SurveyObserver::CheckRequirementsMet()
            {
                if(!StartUpRequirementsMet())
                {
                    return;
                }
                
                if(TimeRequirementMet())
                {
                    m_persistentSettingsModel.SetValue(SurveyOfferedKeyName, true);
                    
                    m_messageBus.Publish(StartUxSurveyMessage());
                }
            }
            
            bool SurveyObserver::StartUpRequirementsMet() const
            {
                return (GetSurveyConditions() & StartUpCountMask) == StartUpRequirementCount;
            }
            
            bool SurveyObserver::SearchRequirementsMet() const
            {
                unsigned int surveyConditions = GetSurveyConditions();
                
                return (surveyConditions & SearchPerformed) && (surveyConditions & SearchResultSelected);
            }
            
            bool SurveyObserver::WeatherRequirementsMet() const
            {
                return (GetSurveyConditions() & WeatherSelected) != 0;
            }
            
            bool SurveyObserver::PinCreationRequirementsMet() const
            {
                return (GetSurveyConditions() & PinCreated) != 0;
            }
            
            bool SurveyObserver::TimeRequirementMet() const
            {
                return (GetSurveyConditions() & TimeSpent) != 0;
            }
        }
    }
}
