// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Modality
    {
        class ModalityChangedMessage
        {
            float m_modality;

        public:
            ModalityChangedMessage(float modality);

            float Modality() const;
        };
    }
}
