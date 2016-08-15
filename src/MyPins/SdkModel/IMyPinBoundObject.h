// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "MyPins.h"
#include "MyPinsSemanticPinType.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class IMyPinBoundObject
            {
            public:
                virtual ~IMyPinBoundObject() {}
                
                virtual void HandlePinCreated(const MyPinModel& pinModel) = 0;
                
                virtual void HandlePinAdded(const MyPinModel& pinModel) = 0;
                
                virtual void HandlePinRemoved(const MyPinModel& pinModel) = 0;
                
                virtual void HandlePinDestroyed(const MyPinModel& pinModel) = 0;
                
                virtual void HandlePinSelected(const MyPinModel& pinModel) = 0;
                
                virtual void HandlePinBecameFullyVisible(const MyPinModel& pinModel) = 0;
                
                virtual void HandlePinBecameFullyInvisible(const MyPinModel& pinModel) = 0;
                
                virtual MyPinsSemanticPinType GetSemanticPinType() const = 0;
                
                virtual std::string GetIconForPin() const = 0;
                
                virtual std::string GetSerialized() const = 0;
            };
        }
    }
}
