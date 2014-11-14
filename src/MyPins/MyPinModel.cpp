// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinModel.h"
#include "Logger.h"

namespace ExampleApp
{
    namespace MyPins
    {
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
        
        void MyPinModel::SelectPin()
        {
            EXAMPLE_LOG("%s pin selected\n", m_title.c_str());
        }
    }
}