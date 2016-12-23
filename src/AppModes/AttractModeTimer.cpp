#include "AttractModeTimer.h"
#include "IUserIdleService.h"

namespace ExampleApp
{
    namespace AppModes
    {
        AttractModeTimer::AttractModeTimer(Eegeo::Input::IUserIdleService& userIdleService, const long long attractModeTimeout)
            : m_userIdleService(userIdleService)
            , m_attractModeTimeout(attractModeTimeout)
        {
        }

        bool AttractModeTimer::IsComplete() const
        {
            return m_userIdleService.GetUserIdleTimeMs() > m_attractModeTimeout;
        }
    }
}
