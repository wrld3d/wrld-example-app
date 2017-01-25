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
                                                                                     const std::string& pinMetadataJson,
                                                                                     const std::string& pinIconKey,
                                                                                     MyPinsFileIO& myPinsFileIO,
                                                                                     ExampleAppMessaging::TMessageBus& messageBus,
                                                                                     MyPins::SdkModel::MyPinsWebService& webService)
            {
                const std::string& imagePath = pinMetadataJson;
                return Eegeo_NEW(UserCreatedPinBoundObject)(pinId, imagePath, pinIconKey, myPinsFileIO, messageBus, webService);
            }
            
            UserCreatedPinBoundObject::UserCreatedPinBoundObject(MyPinModel::TPinIdType pinId,
                                                                 Byte* pImageData,
                                                                 size_t imageSize,
                                                                 bool share,
                                                                 const std::string& pinIconKey,
                                                                 MyPinsFileIO& myPinsFileIO,
                                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                                 MyPins::SdkModel::MyPinsWebService& webService)
            : m_pinId(pinId)
            , m_pImageData(pImageData)
            , m_imageSize(imageSize)
            , m_share(share)
            , m_imagePath("")
            , m_pinIconKey(pinIconKey)
            , m_myPinsFileIO(myPinsFileIO)
            , m_messageBus(messageBus)
            , m_webService(webService)
            {
                Eegeo_ASSERT(!pinIconKey.empty());
            }
            
            UserCreatedPinBoundObject::UserCreatedPinBoundObject(MyPinModel::TPinIdType pinId,
                                                                 const std::string& imagePath,
                                                                 const std::string& pinIconKey,
                                                                 MyPinsFileIO& myPinsFileIO,
                                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                                 MyPins::SdkModel::MyPinsWebService& webService)
            : m_pinId(pinId)
            , m_pImageData(NULL)
            , m_imageSize(0)
            , m_share(false)
            , m_imagePath(imagePath)
            , m_pinIconKey(pinIconKey)
            , m_myPinsFileIO(myPinsFileIO)
            , m_messageBus(messageBus)
            , m_webService(webService)
            {
                Eegeo_ASSERT(!pinIconKey.empty());
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
                return m_pinIconKey;
            }
            
            std::string UserCreatedPinBoundObject::GetSerialized() const
            {
                return m_imagePath;
            }
            
            void UserCreatedPinBoundObject::SubmitPinToWebService(const MyPinModel& pinModel)
            {
                m_webService.SubmitUserCreatedPin(pinModel);
            }
        }
    }
}
