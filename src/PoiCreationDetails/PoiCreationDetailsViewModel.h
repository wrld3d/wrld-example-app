// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IPoiCreationDetailsViewModel.h"
#include "CallbackCollection.h"
#include "PoiCreationDetailsOpenableControl.h"
#include "Reaction.h"

namespace ExampleApp
{
    namespace PoiCreationDetails
    {
        class PoiCreationDetailsViewModel : public IPoiCreationDetailsViewModel, private Eegeo::NonCopyable
        {
            Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
            Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
            PoiCreationDetailsOpenableControl m_openable;
            
        public:
            PoiCreationDetailsViewModel(Eegeo::Helpers::TIdentity identity, Reaction::IReactionControllerModel& reactionControllerModel);
            
            ~PoiCreationDetailsViewModel();
            
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
