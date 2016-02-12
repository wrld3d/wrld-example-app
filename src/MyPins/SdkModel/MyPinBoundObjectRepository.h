// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include "MyPins.h"
#include "MyPinModel.h"
#include "IMyPinBoundObjectRepository.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinBoundObjectRepository : public IMyPinBoundObjectRepository, private Eegeo::NonCopyable
            {
                typedef std::map<MyPinModel::TPinIdType, IMyPinBoundObject*> TStorage;
                
                TStorage m_repository;
                
            public:
                void AddBoundItemForPin(MyPinModel::TPinIdType pinId, IMyPinBoundObject& item);
                
                void RemoveBoundItemForPin(MyPinModel::TPinIdType pinId);
                
                IMyPinBoundObject& GetBoundObjectForPin(const MyPinModel& myPinModel);
            };
        }
    }
}
