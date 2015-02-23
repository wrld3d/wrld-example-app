// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "VectorMath.h"
#include "WorldPinsInFocusModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            class IWorldPinInFocusViewModel
            {
            public:
                virtual ~IWorldPinInFocusViewModel() { }

                virtual const SdkModel::WorldPinsInFocusModel& GetWorldPinsInFocusModel() const = 0;

                virtual bool IsOpen() const = 0;

                virtual const Eegeo::v2& ScreenLocation() const = 0;

                virtual void SelectFocussedResult() = 0;

                virtual void Open(const SdkModel::WorldPinsInFocusModel& worldPinInFocusModel, const Eegeo::v2& screenPos) = 0;

                virtual void Close() = 0;

                virtual void UpdateScreenLocation(const Eegeo::v2& screenPos) = 0;

                virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void InsertUpdateCallback(Eegeo::Helpers::ICallback0& updateCallback) = 0;

                virtual void RemoveUpdateCallback(Eegeo::Helpers::ICallback0& updateCallback) = 0;
            };
        }
    }
}
