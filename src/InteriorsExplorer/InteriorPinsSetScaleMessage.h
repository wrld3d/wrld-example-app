// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        class InteriorPinsSetScaleMessage
        {
        public:
            InteriorPinsSetScaleMessage(float scale);

            float GetScale() const;

        private:
            float m_scale;
        };
    }
}
