
#include "ReactionScreenStateProvider.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            void ReactionScreenStateProvider::SetState(
                    ScreenControl::View::TScreenControlViewState state)
            {
                m_state = state;
                m_updatedCallbacks.ExecuteCallbacks();
            }

            ScreenControl::View::TScreenControlViewState ReactionScreenStateProvider::GetState() const
            {
                return m_state;
            }

            void ReactionScreenStateProvider::InsertStateUpdatedCallback(
                    Eegeo::Helpers::ICallback0 &updateCallback)
            {
                m_updatedCallbacks.AddCallback(updateCallback);
            }

            void ReactionScreenStateProvider::RemoveStateUpdatedCallback(
                    Eegeo::Helpers::ICallback0 &updateCallback)
            {
                m_updatedCallbacks.RemoveCallback(updateCallback);
            }
        }
    }
}
