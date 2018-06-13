
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
                    ScreenControl::View::IMultiStateScreenControlViewModel& screenControlToMove,
                    IReactionScreenStateProvider& offsetProvider)
                    : m_openableControl(openableControlViewModel)
                    , m_screenControlToMove(screenControlToMove)
                    , m_offsetProvider(offsetProvider)
                    , m_offsetUpdateCallback(this, &ReactionPushScreenControl::Perform)
            {
                m_offsetProvider.InsertStateUpdatedCallback(m_offsetUpdateCallback);
            }

            ReactionPushScreenControl::~ReactionPushScreenControl()
            {
                m_offsetProvider.RemoveStateUpdatedCallback(m_offsetUpdateCallback);
            }

            Eegeo::Helpers::TIdentity ReactionPushScreenControl::ReactionToOpenableIdentity()
            {
                return m_openableControl.GetIdentity();
            }

            void ReactionPushScreenControl::Perform()
            {
                m_screenControlToMove.SetState(m_offsetProvider.GetState());
            }
        }
    }
}
