// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UserCreatedMyPinDetailsModelSelectedMessage.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        UserCreatedMyPinDetailsModelSelectedMessage::UserCreatedMyPinDetailsModelSelectedMessage(MyPins::SdkModel::MyPinModel::TPinIdType pinId,
                                                                                                 const std::string& title,
                                                                                                 const std::string& description,
                                                                                                 const std::string& imagePath)
        : m_pinId(pinId)
        , m_title(title)
        , m_description(description)
        , m_imagePath(imagePath)
        {
            
        }
        
        
        MyPins::SdkModel::MyPinModel::TPinIdType UserCreatedMyPinDetailsModelSelectedMessage::GetMyPinId() const
        {
            return m_pinId;
        }
        
        const std::string& UserCreatedMyPinDetailsModelSelectedMessage::GetMyPinTitle() const
        {
            return m_title;
        }
        
        const std::string& UserCreatedMyPinDetailsModelSelectedMessage::GetMyPinDescription() const
        {
            return m_description;
        }
        
        const std::string& UserCreatedMyPinDetailsModelSelectedMessage::GetImagePath() const
        {
            return m_imagePath;
        }

    }
}
