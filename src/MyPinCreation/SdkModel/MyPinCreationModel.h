// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinCreationModel.h"
#include "CallbackCollection.h"
#include "VectorMath.h"
#include "IPlatformAbstractionModule.h"
#include "IWorkPool.h"
#include "MyPins.h"

#include <vector>

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationModel : public IMyPinCreationModel
        {
        public:
            MyPinCreationModel(MyPins::IMyPinsService& myPinsService);
            
            ~MyPinCreationModel();
            
            const MyPinCreationStage& GetCreationStage() const;
            void SetCreationStage(MyPinCreationStage stage);
            
            const Eegeo::dv3& GetPosition() const;
            void SetPosition(const Eegeo::dv3& position);
            void SetTerrainHeight(float height);
            bool NeedsTerrainHeight() const;
            
            void SavePoi(const std::string& title,
                         const std::string& description,
                         Byte* imageData,
                         size_t imageSize,
                         bool shouldShare);
            
            void AddStateChangedCallback(Eegeo::Helpers::ICallback1<MyPinCreationStage>& stateChangedCallback);
            void RemoveStateChangedCallback(Eegeo::Helpers::ICallback1<MyPinCreationStage>& stateChangedCallback);
            
        private:
            bool m_needsTerrainHeightUpdate;
            MyPinCreationStage m_stage;
            Eegeo::dv3 m_position;
            
            MyPins::IMyPinsService& m_myPinsService;

            Eegeo::Helpers::CallbackCollection1<MyPinCreationStage> m_stateChangedCallbacks;
        };
    }
}