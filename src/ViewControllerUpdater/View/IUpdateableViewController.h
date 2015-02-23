// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace ViewControllerUpdater
    {
        namespace View
        {
            class IUpdateableViewController
            {
            public:
                virtual ~IUpdateableViewController() { }

                virtual void UpdateUiThread(float deltaSeconds) = 0;
            };
        }
    }
}
