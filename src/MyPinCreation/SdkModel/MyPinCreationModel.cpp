// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationModel.h"
#include "IFileIO.h"
#include "IWebLoadRequestFactory.h"
#include "LatLongAltitude.h"
#include "MyPinModel.h"
#include "IMyPinsService.h"
#include "EarthConstants.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            MyPinCreationModel::MyPinCreationModel(MyPins::SdkModel::IMyPinsService& myPinsService)
                : m_stage(Inactive)
                , m_position(Eegeo::dv3::Zero())
                , m_myPinsService(myPinsService)
                , m_needsTerrainHeightUpdate(false)
            {

            }

            MyPinCreationModel::~MyPinCreationModel()
            {

            }

            const MyPinCreationStage& MyPinCreationModel::GetCreationStage() const
            {
                return m_stage;
            }

            void MyPinCreationModel::SetCreationStage(ExampleApp::MyPinCreation::MyPinCreationStage stage)
            {
                m_stage = stage;
                if(stage == Ring)
                {
                    m_needsTerrainHeightUpdate = true;
                }
                m_stateChangedCallbacks.ExecuteCallbacks(m_stage);
            }

            const Eegeo::dv3& MyPinCreationModel::GetPosition() const
            {
                return m_position;
            }

            void MyPinCreationModel::SetPosition(const Eegeo::dv3& position)
            {
                m_position = position;
            }

            void MyPinCreationModel::SetTerrainHeight(float height)
            {
                m_position = m_position.Norm() * (Eegeo::Space::EarthConstants::Radius + height);
                m_needsTerrainHeightUpdate = false;
            }

            bool MyPinCreationModel::NeedsTerrainHeight() const
            {
                return m_needsTerrainHeightUpdate;
            }

            void MyPinCreationModel::SavePoi(const std::string& title,
                                             const std::string& description,
                                             const std::string& ratingsImage,
                                             const int reviewCount,
                                             Byte* imageData,
                                             size_t imageSize,
                                             bool shouldShare)
            {
                m_myPinsService.SaveUserCreatedPoiPin(title,
                                                      description,
                                                      ratingsImage,
                                                      reviewCount,
                                                      Eegeo::Space::LatLong::FromECEF(m_position),
                                                      imageData,
                                                      imageSize,
                                                      shouldShare);

                SetCreationStage(Inactive);
            }

            void MyPinCreationModel::InsertStateChangedCallback(Eegeo::Helpers::ICallback1<MyPinCreationStage>& stateChangedCallback)
            {
                m_stateChangedCallbacks.AddCallback(stateChangedCallback);
            }

            void MyPinCreationModel::RemoveStateChangedCallback(Eegeo::Helpers::ICallback1<MyPinCreationStage>& stateChangedCallback)
            {
                m_stateChangedCallbacks.RemoveCallback(stateChangedCallback);
            }
        }
    }
}
