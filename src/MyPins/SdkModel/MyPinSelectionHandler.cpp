// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinSelectionHandler.h"
#include "IMyPinBoundObjectRepository.h"
#include "IMyPinBoundObject.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinSelectionHandler::MyPinSelectionHandler(MyPinModel& myPinModel,
                                                         MyPins::SdkModel::IMyPinBoundObjectRepository& myPinBoundObjectRepository,
                                                         Metrics::IMetricsService& metricsService)
                : m_myPinModel(myPinModel)
                , m_myPinBoundObjectRepository(myPinBoundObjectRepository)
                , m_metricsService(metricsService)
            {

            }

            void MyPinSelectionHandler::SelectPin()
            {
                m_metricsService.SetEvent("Selected MyPin", "Name", m_myPinModel.GetTitle().c_str());
                IMyPinBoundObject& myPinBoundObject(m_myPinBoundObjectRepository.GetBoundObjectForPin(m_myPinModel));
                myPinBoundObject.HandlePinSelected(m_myPinModel);
            }
        }
    }
}
