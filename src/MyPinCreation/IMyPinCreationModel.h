// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "MyPinCreationStage.h"
#include "ICallback.h"
#include "VectorMathDecl.h"
#include "Types.h"

#include <string>

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class IMyPinCreationModel
        {
        public:
            virtual ~IMyPinCreationModel() { }
            
            virtual const MyPinCreationStage& GetCreationStage() const = 0;
            virtual void SetCreationStage(MyPinCreationStage stage) = 0;
            
            virtual const Eegeo::dv3& GetPosition() const = 0;
            virtual void SetPosition(const Eegeo::dv3& position) = 0;
            
            virtual void SavePoi(const std::string& title,
                                 const std::string& description,
                                 Byte* imageData,
                                 size_t imageSize,
                                 bool shouldShare) = 0;
            
            virtual void AddStateChangedCallback(Eegeo::Helpers::ICallback1<MyPinCreationStage>& stateChangedCallback) = 0;
            virtual void RemoveStateChangedCallback(Eegeo::Helpers::ICallback1<MyPinCreationStage>& stateChangedCallback) = 0;
        };
    }
}