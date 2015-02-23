// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationViewSavePinMessage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        MyPinCreationViewSavePinMessage::MyPinCreationViewSavePinMessage(const std::string& title,
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

        MyPinCreationViewSavePinMessage::~MyPinCreationViewSavePinMessage()
        {

        }

        const std::string& MyPinCreationViewSavePinMessage::GetTitle() const
        {
            return m_title;
        }

        const std::string& MyPinCreationViewSavePinMessage::GetDescription() const
        {
            return m_description;
        }

        Byte* MyPinCreationViewSavePinMessage::GetImageData() const
        {
            return m_pImageData;
        }

        size_t MyPinCreationViewSavePinMessage::GetImageSize() const
        {
            return m_imageSize;
        }

        bool MyPinCreationViewSavePinMessage::GetShouldShare() const
        {
            return m_shouldShare;
        }
    }
}
