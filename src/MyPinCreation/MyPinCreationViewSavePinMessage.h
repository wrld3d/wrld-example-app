// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationViewSavePinMessage
        {
        public:
            MyPinCreationViewSavePinMessage(const std::string& title,
                                            const std::string& description,
                                            Byte* pImageData,
                                            size_t imageSize,
                                            bool shouldShare)
            : m_title(title)
            , m_description(description)
            , m_pImageData(pImageData)
            , m_imageSize(imageSize)
            , m_shouldShare(shouldShare)
            {
                
            }
            
            ~MyPinCreationViewSavePinMessage()
            {
                
            }
            
            const std::string& GetTitle() const
            {
                return m_title;
            }
            
            const std::string& GetDescription() const
            {
                return m_description;
            }
            
            Byte* GetImageData() const
            {
                return m_pImageData;
            }
            
            size_t GetImageSize() const
            {
                return m_imageSize;
            }
            
            bool GetShouldShare() const
            {
                return m_shouldShare;
            }
            
        private:
            std::string m_title;
            std::string m_description;
            Byte* m_pImageData;
            size_t m_imageSize;
            bool m_shouldShare;
        };
    }
}