// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Search.h"
#include "ICallback.h"
#include "MyPins.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class IMyPinDetailsViewModel
            {
            public:
                virtual ~IMyPinDetailsViewModel() { }
                
                virtual MyPins::SdkModel::MyPinModel::TPinIdType GetMyPinId() const = 0;
                
                virtual const std::string& GetMyPinTitle() const = 0;
                
                virtual const std::string& GetMyPinDescription() const = 0;
                
                virtual const std::string& GetImagePath() const = 0;

                virtual bool TryAcquireReactorControl() = 0;

                virtual bool IsOpen() const = 0;

                virtual void Open(MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                  const std::string& title,
                                  const std::string& description,
                                  const std::string& imagePath) = 0;

                virtual void Close() = 0;

                virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
            };
        }
    }
}
