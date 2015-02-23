// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "IViewControllerUpdaterModel.h"
#include "ViewControllerUpdater.h"

namespace ExampleApp
{
    namespace ViewControllerUpdater
    {
        namespace View
        {
            class ViewControllerUpdaterModel: public IViewControllerUpdaterModel, private Eegeo::NonCopyable
            {
            private:
                std::vector<IUpdateableViewController*> m_updateTargetsUi;

            public:
                ViewControllerUpdaterModel();

                ~ViewControllerUpdaterModel();

                void AddUpdateableObject(IUpdateableViewController& updateProtocolImplementation);

                void RemoveUpdateableObject(IUpdateableViewController& updateProtocolImplementation);

                void UpdateObjectsUiThread(float deltaSeconds);
            };
        }
    }
}

