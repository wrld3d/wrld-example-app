// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IAboutPageViewModel.h"
#include "CallbackCollection.h"
#include "AboutPageOpenableControl.h"
#include "Reaction.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        class AboutPageViewModel : public IAboutPageViewModel, private Eegeo::NonCopyable
        {
            Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
            Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
            AboutPageOpenableControl m_openable;
            
        public:
            AboutPageViewModel(Eegeo::Helpers::TIdentity identity, Reaction::IReactionControllerModel& reactionControllerModel);
            
            ~AboutPageViewModel();
            
            bool TryAcquireReactorControl();
            
            bool IsOpen() const;
            
            void Open();
            
            void Close();
            
            OpenableControlViewModel::IOpenableControlViewModel& GetOpenableControl();
            
            void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);
            
            void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);
            
            void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
            
            void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
        };
    }
}
