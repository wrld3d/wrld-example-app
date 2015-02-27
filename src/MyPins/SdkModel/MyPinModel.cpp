// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            const int MyPinModel::CurrentVersion = 1;
            
            MyPinModel::MyPinModel()
                : m_version(-1)
                , m_modelId(-1)
                , m_latLong(0.0, 0.0)
            {

            }

            MyPinModel::MyPinModel(int version,
                                   int modelId,
                                   const std::string& title,
                                   const std::string& description,
                                   int sdkMapPinIconIndex,
                                   const Eegeo::Space::LatLong& latLong)
            : m_version(version)
            , m_modelId(modelId)
            , m_title(title)
            , m_description(description)
            , m_sdkMapPinIconIndex(sdkMapPinIconIndex)
            , m_latLong(latLong)
            {
                
            }
        }
    }
}
