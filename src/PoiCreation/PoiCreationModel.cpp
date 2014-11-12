// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationModel.h"
#include "IFileIO.h"
#include "IWebLoadRequestFactory.h"
#include "LatLongAltitude.h"
#include "MyPinModel.h"
#include "IMyPinsService.h"

namespace ExampleApp
{
    namespace PoiCreation
    {
        PoiCreationModel::PoiCreationModel(MyPins::IMyPinsService& myPinsService)
        : m_stage(Inactive)
        , m_position(Eegeo::dv3::Zero())
        , m_myPinsService(myPinsService)
        {
            
        }
        
        PoiCreationModel::~PoiCreationModel()
        {
            
        }
        
        const PoiCreationStage& PoiCreationModel::GetCreationStage() const
        {
            return m_stage;
        }
        
        void PoiCreationModel::SetCreationStage(ExampleApp::PoiCreation::PoiCreationStage stage)
        {
            m_stage = stage;
            m_stateChangedCallbacks.ExecuteCallbacks(m_stage);
        }
        
        const Eegeo::dv3& PoiCreationModel::GetPosition() const
        {
            return m_position;
        }
        
        void PoiCreationModel::SetPosition(const Eegeo::dv3& position)
        {
            m_position = position;
        }
        
        void PoiCreationModel::SavePoi(const std::string& title,
                                       const std::string& description,
                                       Byte* imageData,
                                       size_t imageSize,
                                       bool shouldShare)
        {
            m_myPinsService.SavePin(title,
                                    description,
                                    Eegeo::Space::LatLong::FromECEF(m_position),
                                    imageData,
                                    imageSize,
                                    shouldShare);
            
            SetCreationStage(Inactive);
        }
        
        void PoiCreationModel::AddStateChangedCallback(Eegeo::Helpers::ICallback1<PoiCreationStage>& stateChangedCallback)
        {
            m_stateChangedCallbacks.AddCallback(stateChangedCallback);
        }
        
        void PoiCreationModel::RemoveStateChangedCallback(Eegeo::Helpers::ICallback1<PoiCreationStage>& stateChangedCallback)
        {
            m_stateChangedCallbacks.RemoveCallback(stateChangedCallback);
        }
    }
}