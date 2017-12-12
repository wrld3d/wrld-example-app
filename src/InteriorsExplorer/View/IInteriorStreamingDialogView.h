// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class IInteriorStreamingDialogView
            {
            public:

                virtual ~IInteriorStreamingDialogView() { }

                virtual void Show() = 0;
                virtual void Hide(bool interiorLoaded) = 0;

            };
        }
    }
}

