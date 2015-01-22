// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Modality
    {
        class UpdateNativeModalBackgroundMessage
        {
            float m_modality;

        public:
            UpdateNativeModalBackgroundMessage(float modality);

            float Modality() const;
        };
    }
}
