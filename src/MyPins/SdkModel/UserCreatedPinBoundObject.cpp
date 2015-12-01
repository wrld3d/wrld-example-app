// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UserCreatedPinBoundObject.h"
#include "MyPinsFileIO.h"
#include "UserCreatedMyPinDetailsModelSelectedMessage.h"
#include "MyPinsWebService.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            UserCreatedPinBoundObject* UserCreatedPinBoundObject::FromSerializedData(MyPinModel::TPinIdType pinId,
                                                                                     const std::string& serializedData,
                                                                                     MyPinsFileIO& myPinsFileIO,
                                                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                                                     MyPins::SdkModel::MyPinsWebService& webService)
            {
                return Eegeo_NEW(UserCreatedPinBoundObject)(pinId, serializedData, myPinsFileIO, messageBus, webService);
            }
            
            UserCreatedPinBoundObject::UserCreatedPinBoundObject(MyPinModel::TPinIdType pinId,
                                                                 Byte* pImageData,
                                                                 size_t imageSize,
                                                                 bool share,
                                                                 MyPinsFileIO& myPinsFileIO,
                                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                                 MyPins::SdkModel::MyPinsWebService& webService)
            : m_pinId(pinId)
            , m_pImageData(pImageData)
            , m_imageSize(imageSize)
            , m_share(share)
            , m_imagePath("")
            , m_myPinsFileIO(myPinsFileIO)
            , m_messageBus(messageBus)
            , m_webService(webService)
            {
                
            }
            
            UserCreatedPinBoundObject::UserCreatedPinBoundObject(MyPinModel::TPinIdType pinId,
                                                                 const std::string& imagePath,
                                                                 MyPinsFileIO& myPinsFileIO,
                                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                                 MyPins::SdkModel::MyPinsWebService& webService)
            : m_pinId(pinId)
            , m_pImageData(NULL)
            , m_imageSize(0)
            , m_share(false)
            , m_imagePath(imagePath)
            , m_myPinsFileIO(myPinsFileIO)
            , m_messageBus(messageBus)
            , m_webService(webService)
            {
                
            }
            
            UserCreatedPinBoundObject::~UserCreatedPinBoundObject()
            {
                
            }
            
            void UserCreatedPinBoundObject::HandlePinCreated(const MyPinModel& pinModel)
            {
                if (m_pImageData != NULL)
                {
                    m_myPinsFileIO.TryCacheImageToDisk(m_pImageData, m_imageSize, m_pinId, m_imagePath);
                }
                
                m_myPinsFileIO.SavePinModelToDisk(pinModel);
                
                if (m_share)
                {
                    SubmitPinToWebService(pinModel);
                }
            }
            
            void UserCreatedPinBoundObject::HandlePinAdded(const MyPinModel& pinModel)
            {
                // Nothing to do.
            }
            
            void UserCreatedPinBoundObject::HandlePinRemoved(const MyPinModel& pinModel)
            {
                // Nothing to do.
            }
            
            void UserCreatedPinBoundObject::HandlePinDestroyed(const MyPinModel& pinModel)
            {
                if (!m_imagePath.empty())
                {
                    m_myPinsFileIO.DeleteImageFromDisk(m_imagePath);
                }
            }
            
            void UserCreatedPinBoundObject::HandlePinSelected(const MyPinModel& pinModel)
            {
                m_messageBus.Publish(MyPinDetails::UserCreatedMyPinDetailsModelSelectedMessage(pinModel.Identifier(),
                                                                                               pinModel.GetTitle(),
                                                                                               pinModel.GetDescription(),
                                                                                               m_imagePath));
            }
            
            void UserCreatedPinBoundObject::HandlePinBecameFullyVisible(const MyPinModel& pinModel)
            {
                // Nothing to do.
            }
            
            void UserCreatedPinBoundObject::HandlePinBecameFullyInvisible(const MyPinModel& pinModel)
            {
                // Nothing to do.
            }
            
            MyPinsSemanticPinType UserCreatedPinBoundObject::GetSemanticPinType() const
            {
                return UserCreatedPoi;
            }
            
            std::string UserCreatedPinBoundObject::GetIconForPin() const
            {
                return "place";
            }
            
            const std::string& UserCreatedPinBoundObject::GetSerialized() const
            {
                return m_imagePath;
            }
            
            void UserCreatedPinBoundObject::SubmitPinToWebService(const MyPinModel& pinModel)
            {
                m_webService.SubmitUserCreatedPin(pinModel, m_imagePath);
            }
        }
    }
}
