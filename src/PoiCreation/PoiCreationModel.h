// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IPoiCreationModel.h"
#include "CallbackCollection.h"
#include "VectorMath.h"
#include "IPlatformAbstractionModule.h"
#include "IWorkPool.h"
#include "MyPins.h"

#include <vector>

namespace ExampleApp
{
    namespace PoiCreation
    {
        class PoiCreationModel : public IPoiCreationModel
        {
        public:
            PoiCreationModel(MyPins::IMyPinsService& myPinsService);
            
            ~PoiCreationModel();
            
            const PoiCreationStage& GetCreationStage() const;
            void SetCreationStage(PoiCreationStage stage);
            
            const Eegeo::dv3& GetPosition() const;
            void SetPosition(const Eegeo::dv3& position);
            
            void SavePoi(const std::string& title,
                         const std::string& description,
                         Byte* imageData,
                         size_t imageSize,
                         bool shouldShare);
            
            void AddStateChangedCallback(Eegeo::Helpers::ICallback1<PoiCreationStage>& stateChangedCallback);
            void RemoveStateChangedCallback(Eegeo::Helpers::ICallback1<PoiCreationStage>& stateChangedCallback);
            
        private:
            PoiCreationStage m_stage;
            Eegeo::dv3 m_position;
            
            MyPins::IMyPinsService& m_myPinsService;

            Eegeo::Helpers::CallbackCollection1<PoiCreationStage> m_stateChangedCallbacks;
        };
    }
}