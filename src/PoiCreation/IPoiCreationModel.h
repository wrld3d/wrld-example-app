// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "PoiCreationStage.h"
#include "ICallback.h"
#include "VectorMathDecl.h"
#include "Types.h"

#include <string>

namespace ExampleApp
{
    namespace PoiCreation
    {
        class IPoiCreationModel
        {
        public:
            virtual ~IPoiCreationModel() { }
            
            virtual const PoiCreationStage& GetCreationStage() const = 0;
            virtual void SetCreationStage(PoiCreationStage stage) = 0;
            
            virtual const Eegeo::dv3& GetPosition() const = 0;
            virtual void SetPosition(const Eegeo::dv3& position) = 0;
            
            virtual void SavePoi(const std::string& title,
                                 const std::string& description,
                                 Byte* imageData,
                                 size_t imageSize,
                                 bool shouldShare) = 0;
            
            virtual void AddStateChangedCallback(Eegeo::Helpers::ICallback1<PoiCreationStage>& stateChangedCallback) = 0;
            virtual void RemoveStateChangedCallback(Eegeo::Helpers::ICallback1<PoiCreationStage>& stateChangedCallback) = 0;
        };
    }
}