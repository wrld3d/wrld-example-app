
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
                    IReactionScreenOffsetProvider& offsetProvider)
                    : m_openableControl(openableControlViewModel)
                    , m_screenControlToMove(screenControlToMove)
                    , m_offsetProvider(offsetProvider)
                    , m_offsetUpdateCallback(this, &ReactionPushScreenControl::Update)
            {
                m_offsetProvider.InsertOffsetUpdatedCallback(m_offsetUpdateCallback);
            }

            ReactionPushScreenControl::~ReactionPushScreenControl()
            {
                m_offsetProvider.RemoveOffsetUpdatedCallback(m_offsetUpdateCallback);
            }

            Eegeo::Helpers::TIdentity ReactionPushScreenControl::ReactionToOpenableIdentity()
            {
                return m_openableControl.GetIdentity();
            }

            void ReactionPushScreenControl::Perform()
            {
                m_screenControlToMove.SetOffsetFromDefaultPosition(
                        m_openableControl.IsOpen() ? m_offsetProvider.GetOffset() : 0.0f );
            }

            void ReactionPushScreenControl::Update()
            {
                if(m_openableControl.IsOpen())
                {
                    m_screenControlToMove.SetOffsetFromDefaultPosition(m_offsetProvider.GetOffset());
                }
            }
        }
    }
}
