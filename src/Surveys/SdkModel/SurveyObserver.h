// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Types.h"

#include "BidirectionalBus.h"
#include "CategorySearchSelectedMessage.h"
#include "ICallback.h"
#include "MyPinCreationViewSavePinMessage.h"
#include "PersistentSettings.h"
#include "SearchMenuPerformedSearchMessage.h"
#include "SearchResultMenuItemSelectedMessage.h"
#include "WeatherSelectedMessage.h"

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
                Eegeo::Helpers::TCallback1<SurveyObserver, const CategorySearch::CategorySearchSelectedMessage&> m_onCategorySearchPerformedMessage;
                Eegeo::Helpers::TCallback1<SurveyObserver, const SearchResultMenu::SearchResultMenuItemSelectedMessage&> m_onSearchResultSelected;
                Eegeo::Helpers::TCallback1<SurveyObserver, const WeatherMenu::WeatherSelectedMessage&> m_onWeatherSelected;
                Eegeo::Helpers::TCallback1<SurveyObserver, const MyPinCreation::MyPinCreationViewSavePinMessage&> m_onPinCreated;
                
                void OnSearchPerformedMessage(const SearchMenu::SearchMenuPerformedSearchMessage& message);
                void OnCategorySearchPerformedMessage(const CategorySearch::CategorySearchSelectedMessage& message);
                void OnSearchResultSelected(const SearchResultMenu::SearchResultMenuItemSelectedMessage& message);
                void OnWeatherSelected(const WeatherMenu::WeatherSelectedMessage& message);
                void OnPinCreated(const MyPinCreation::MyPinCreationViewSavePinMessage& message);
                
                bool SurveyOffered();
                
                unsigned int GetSurveyConditions() const;
                void SetSurveyConditions(unsigned int surveyConditions);
                void SetSurveyConditionsFlag(unsigned int conditionFlag);
                
                void CheckRequirementsMet();
                
                bool StartUpRequirementsMet() const;
                bool SearchRequirementsMet() const;
                bool WeatherRequirementsMet() const;
                bool PinCreationRequirementsMet() const;
                
            public:
                SurveyObserver(ExampleAppMessaging::TMessageBus& messageBus,
                               PersistentSettings::IPersistentSettingsModel& persistentSettingsModel);
                
                ~SurveyObserver();
                
                void OnStartup();
            };
        }
    }
}
