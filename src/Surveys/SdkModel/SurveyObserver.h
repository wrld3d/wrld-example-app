// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Types.h"

#include "BidirectionalBus.h"
#include "TagSearchSelectedMessage.h"
#include "ICallback.h"
#include "MyPinCreationViewSavePinMessage.h"
#include "PersistentSettings.h"
#include "SearchMenuPerformedSearchMessage.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "WeatherSelectedMessage.h"
#include "SurveyTimeRequirementMetMessage.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace SdkModel
        {
            class SurveyObserver : private Eegeo::NonCopyable
            {
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;
                PersistentSettings::IPersistentSettingsModel& m_persistentSettingsModel;
                
                Eegeo::Helpers::TCallback1<SurveyObserver, const SearchMenu::SearchMenuPerformedSearchMessage&> m_onSearchPerformedMessage;
                Eegeo::Helpers::TCallback1<SurveyObserver, const TagSearch::TagSearchSelectedMessage&> m_onTagSearchPerformedMessage;
                Eegeo::Helpers::TCallback1<SurveyObserver, const SearchResultSection::SearchResultSectionItemSelectedMessage&> m_onSearchResultSelected;
                Eegeo::Helpers::TCallback1<SurveyObserver, const WeatherMenu::WeatherSelectedMessage&> m_onWeatherSelected;
                Eegeo::Helpers::TCallback1<SurveyObserver, const MyPinCreation::MyPinCreationViewSavePinMessage&> m_onPinCreated;
                Eegeo::Helpers::TCallback1<SurveyObserver, const SurveyTimeRequirementMetMessage&> m_onSurveyTimeRequirementMet;
                
                void OnSearchPerformedMessage(const SearchMenu::SearchMenuPerformedSearchMessage& message);
                void OnTagSearchPerformedMessage(const TagSearch::TagSearchSelectedMessage& message);
                void OnSearchResultSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message);
                void OnWeatherSelected(const WeatherMenu::WeatherSelectedMessage& message);
                void OnPinCreated(const MyPinCreation::MyPinCreationViewSavePinMessage& message);
                void OnTimeSpentInApp(const SurveyTimeRequirementMetMessage& message);
                
                bool SurveyOffered();
                
                unsigned int GetSurveyConditions() const;
                void SetSurveyConditions(unsigned int surveyConditions);
                void SetSurveyConditionsFlag(unsigned int conditionFlag);
                
                void CheckRequirementsMet();
                
                bool StartUpRequirementsMet() const;
                bool SearchRequirementsMet() const;
                bool WeatherRequirementsMet() const;
                bool PinCreationRequirementsMet() const;
                bool TimeRequirementMet() const;
                
            public:
                SurveyObserver(ExampleAppMessaging::TMessageBus& messageBus,
                               PersistentSettings::IPersistentSettingsModel& persistentSettingsModel);
                
                ~SurveyObserver();
                
                void OnStartup();
            };
        }
    }
}
