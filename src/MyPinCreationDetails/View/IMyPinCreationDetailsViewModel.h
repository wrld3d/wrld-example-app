// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICallback.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        class IMyPinCreationDetailsViewModel
        {
        public:
            ~IMyPinCreationDetailsViewModel(){ }
            
            virtual bool TryAcquireReactorControl() = 0;
            
            virtual bool IsOpen() const = 0;
            
            virtual void Open() = 0;
            
            virtual void Close() = 0;
            
            virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;
            
            virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;
            
            virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
            
            virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
            
        };
    }
}