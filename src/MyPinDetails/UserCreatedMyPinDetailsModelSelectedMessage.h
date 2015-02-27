// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        class UserCreatedMyPinDetailsModelSelectedMessage
        {
        private:
            MyPins::SdkModel::MyPinModel::TPinIdType m_pinId;
            std::string m_title;
            std::string m_description;
            std::string m_imagePath;

        public:
            UserCreatedMyPinDetailsModelSelectedMessage(MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                                        const std::string& title,
                                                        const std::string& description,
                                                        const std::string& imagePath);
            
            MyPins::SdkModel::MyPinModel::TPinIdType GetMyPinId() const;
            
            const std::string& GetMyPinTitle() const;
            
            const std::string& GetMyPinDescription() const;
            
            const std::string& GetImagePath() const;
        };
    }
}
