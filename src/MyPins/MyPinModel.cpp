// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinModel::MyPinModel(unsigned int modelId,
                               std::string title,
                               std::string description,
                               std::string imagePath,
                               Eegeo::Space::LatLong latLong,
                               bool shouldShare)
        : m_latLong(latLong)
//        : m_modelId(modelId)
//        , m_title(title)
//        , m_description(description)
//        , m_imagePath(imagePath)
//        , m_latLong(latLong)
//        , m_shouldShare(shouldShare)
        {
            
        }
    }
}