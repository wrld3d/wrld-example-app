// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Modality
    {
        class UpdateNativeModalBackgroundMessage
        {
            float m_modality;
            bool m_fixed;

        public:
            UpdateNativeModalBackgroundMessage(float modality, bool fixed);

            float Modality() const;
            bool ShouldFixOn() const;
        };
    }
}
