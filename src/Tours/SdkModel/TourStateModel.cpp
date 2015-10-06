// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourStateModel.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            TourStateModel::TourStateModel(const std::string& headline,
                                           const std::string& description,
                                           const std::string& imagePath,
                                           const std::string& icon)
            : m_headline(headline)
            , m_description(description)
            , m_imagePath(imagePath)
            , m_icon(icon)
            {
                
            }
            
            const std::string& TourStateModel::Headline() const
            {
                return m_headline;
            }
            
            const std::string& TourStateModel::Description() const
            {
                return m_description;
            }
            
            const std::string& TourStateModel::ImagePath() const
            {
                return m_imagePath;
            }
            
            const std::string& TourStateModel::Icon() const
            {
                return m_icon;
            }
        }
    }
}
