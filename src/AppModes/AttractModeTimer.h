#pragma once

#include "IUserIdleService.h"

namespace ExampleApp
{
    namespace AppModes
    {
        class AttractModeTimer
        {
        public:
            AttractModeTimer(Eegeo::Input::IUserIdleService& userIdleService, const long long attractModeTimeout);
            bool IsComplete() const;

        private:
            Eegeo::Input::IUserIdleService& m_userIdleService;
            const long long m_attractModeTimeout;
        };
    }
}