// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinModel::MyPinModel()
                : m_modelId(-1)
                , m_latLong(0.0, 0.0)
            {

            }

            MyPinModel::MyPinModel(int modelId,
                                   const std::string& title,
                                   const std::string& description,
                                   int sdkMapPinIconIndex,
                                   const Eegeo::Space::LatLong& latLong,
                                   const MyPinsSemanticPinType& semanticPinType,
                                   const std::string& pinTypeMetadata)
            : m_modelId(modelId)
            , m_title(title)
            , m_description(description)
            , m_sdkMapPinIconIndex(sdkMapPinIconIndex)
            , m_latLong(latLong)
            , m_semanticPinType(semanticPinType)
            , m_pinTypeMetadata(pinTypeMetadata)
            {
                
            }
        }
    }
}
