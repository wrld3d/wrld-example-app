
#include "IIdentity.h"
#include "IReaction.h"
#include "IScreenControlViewModel.h"
#include "ReactionPushScreenControl.h"
#include <vector>
#include <OpenableControl/View/IOpenableControlViewModel.h>

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            ReactionPushScreenControl::ReactionPushScreenControl(
                    const OpenableControl::View::IOpenableControlViewModel& openableControlViewModel,
                    ScreenControl::View::IMovableScreenControlViewModel& screenControlToMove,
                    const ScreenControl::View::IScreenControlViewPosition destination)
                    : m_openableControl(openableControlViewModel)
                    , m_screenControlToMove(screenControlToMove), m_destination(destination)
            {

            }

            Eegeo::Helpers::TIdentity ReactionPushScreenControl::ReactionToOpenableIdentity()
            {
                return m_openableControl.GetIdentity();
            }

            void ReactionPushScreenControl::Perform()
            {
                m_screenControlToMove.SetOnScreenPosition(m_destination * m_openableControl.OpenState());
            }
        }
    }
}
