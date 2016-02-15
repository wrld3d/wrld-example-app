// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "EegeoSearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoSearchResultModel::EegeoSearchResultModel()
                : m_phone("")
                , m_webUrl("")
                , m_imageUrl("")
                {
                    
                }
                
                EegeoSearchResultModel::EegeoSearchResultModel(const std::string& phone,
                                                     const std::string& webUrl,
                                                     const std::string& imageUrl)
                    : m_phone(phone)
                    , m_webUrl(webUrl)
                    , m_imageUrl(imageUrl)
                {
                }

                EegeoSearchResultModel::~EegeoSearchResultModel()
                {

                }

                const std::string& EegeoSearchResultModel::GetPhone() const
                {
                    return m_phone;
                }

                const std::string& EegeoSearchResultModel::GetWebUrl() const
                {
                    return m_webUrl;
                }

                bool EegeoSearchResultModel::HasImage() const
                {
                    return !m_imageUrl.empty();
                }
                
                const std::string& EegeoSearchResultModel::GetImageUrl() const
                {
                    return m_imageUrl;
                }
            }
        }
    }
}
