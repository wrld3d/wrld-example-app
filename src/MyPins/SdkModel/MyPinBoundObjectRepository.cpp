// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinBoundObjectRepository.h"
#include "Types.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            void MyPinBoundObjectRepository::AddBoundItemForPin(MyPinModel::TPinIdType pinId, IMyPinBoundObject& item)
            {
                std::pair<TStorage::iterator, bool> result = m_repository.insert(std::make_pair(pinId, &item));
                Eegeo_ASSERT(result.second, "Couldn't add binding, key value %d already exists.\n", pinId);
            }
            
            void MyPinBoundObjectRepository::RemoveBoundItemForPin(MyPinModel::TPinIdType pinId)
            {
                TStorage::size_type numErased = m_repository.erase(pinId);
                Eegeo_ASSERT(numErased == 1, "Couldn't remove binding, key value %d not present.\n", pinId);
            }
            
            IMyPinBoundObject& MyPinBoundObjectRepository::GetBoundObjectForPin(const MyPinModel& myPinModel)
            {
                TStorage::iterator result = m_repository.find(myPinModel.Identifier());
                Eegeo_ASSERT(result != m_repository.end(), "Couldn't find bound object, key value %d not present.\n", myPinModel.Identifier());
                return *(result->second);
            }
        }
    }
}
