// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinModel.h"
#include "Logger.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinModel::MyPinModel()
        : m_modelId(-1)
        , m_latLong(0.0, 0.0)
        {
            
        }
        
        MyPinModel::MyPinModel(int modelId,
                               std::string title,
                               std::string description,
                               std::string imagePath,
                               Eegeo::Space::LatLong latLong)
        : m_modelId(modelId)
        , m_title(title)
        , m_description(description)
        , m_imagePath(imagePath)
        , m_latLong(latLong)
        {
            
        }
    }
}