// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "MyPinModel.h"
#include "IMyPinBoundObject.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class UserCreatedPinBoundObject : public IMyPinBoundObject, private Eegeo::NonCopyable
            {
                MyPinModel::TPinIdType m_pinId;
                Byte* m_pImageData;
                size_t m_imageSize;
                bool m_share;
                std::string m_imagePath;
                MyPinsFileIO& m_myPinsFileIO;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                void SubmitPinToWebService(const MyPinModel& pinModel);
                
            public:
                static UserCreatedPinBoundObject* FromSerializedData(MyPinModel::TPinIdType pinId,
                                                                     const std::string& serializedData,
                                                                     MyPinsFileIO& myPinsFileIO,
                                                                     ExampleAppMessaging::TMessageBus& messageBus);
                
                UserCreatedPinBoundObject(MyPinModel::TPinIdType pinId,
                                          Byte* imageData,
                                          size_t imageSize,
                                          bool share,
                                          MyPinsFileIO& myPinsFileIO,
                                          ExampleAppMessaging::TMessageBus& messageBus);
                
                UserCreatedPinBoundObject(MyPinModel::TPinIdType pinId,
                                          const std::string& imagePath,
                                          MyPinsFileIO& myPinsFileIO,
                                          ExampleAppMessaging::TMessageBus& messageBus);
                
                ~UserCreatedPinBoundObject();
                
                void HandlePinCreated(const MyPinModel& pinModel);
                
                void HandlePinAdded(const MyPinModel& pinModel);
                
                void HandlePinRemoved(const MyPinModel& pinModel);
                
                void HandlePinDestroyed(const MyPinModel& pinModel);
                
                void HandlePinSelected(const MyPinModel& pinModel);
                
                void HandlePinBecameFullyVisible(const MyPinModel& pinModel);
                
                void HandlePinBecameFullyInvisible(const MyPinModel& pinModel);
                
                MyPinsSemanticPinType GetSemanticPinType() const;
                
                std::string GetIconForPin() const;
                
                const std::string& GetSerialized() const;
            };
        }
    }
}
