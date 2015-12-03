// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Tours
    {
        class ActiveTourQuitSelectedMessage
        {
        private:
            bool m_exitTours;
        public:
            ActiveTourQuitSelectedMessage(bool exitTours);
            
            bool ExitTours() const;
        };
    }
}
