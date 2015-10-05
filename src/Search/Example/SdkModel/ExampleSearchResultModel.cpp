// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleSearchResultModel.h"

#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include <sstream>

namespace ExampleApp
{
    namespace Search
    {
        namespace Example
        {
            namespace SdkModel
            {
                ExampleSearchResultModel::ExampleSearchResultModel()
                : m_imageUrl("")
                {
                }
                
                ExampleSearchResultModel::ExampleSearchResultModel(
                                                               const std::string& imageUrl)
                : m_imageUrl(imageUrl)
                {
                }
                
                ExampleSearchResultModel::~ExampleSearchResultModel()
                {
                    
                }
                
                const std::string& ExampleSearchResultModel::GetImageUrl() const
                {
                    return m_imageUrl;
                }
                
                
            }
        }
    }
}
