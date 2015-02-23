// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ViewControllerUpdater.h"

namespace ExampleApp
{
    namespace ViewControllerUpdater
    {
        namespace View
        {
            class IViewControllerUpdaterModel
            {
            public:
                virtual ~IViewControllerUpdaterModel() { }

                virtual void AddUpdateableObject(IUpdateableViewController& updateProtocolImplementation) = 0;

                virtual void RemoveUpdateableObject(IUpdateableViewController& updateProtocolImplementation) = 0;

                virtual void UpdateObjectsUiThread(float deltaSeconds) = 0;
            };
        }
    }
}
