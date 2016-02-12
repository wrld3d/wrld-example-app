// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
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
                                            bool shouldShare);

            ~MyPinCreationViewSavePinMessage();

            const std::string& GetTitle() const;

            const std::string& GetDescription() const;

            Byte* GetImageData() const;

            size_t GetImageSize() const;

            bool GetShouldShare() const;

        private:
            std::string m_title;
            std::string m_description;
            std::string m_ratingsImage;
            Byte* m_pImageData;
            size_t m_imageSize;
            bool m_shouldShare;
        };
    }
}
