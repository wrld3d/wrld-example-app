
#include "ReactionScreenOffsetProvider.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            void ReactionScreenOffsetProvider::SetOffset(ScreenControl::View::IScreenControlViewPosition offset)
            {
                m_offset = offset;
                m_updatedCallbacks.ExecuteCallbacks();
            }

            ScreenControl::View::IScreenControlViewPosition ReactionScreenOffsetProvider::GetOffset() const
            {
                return m_offset;
            }

            void ReactionScreenOffsetProvider::InsertOffsetUpdatedCallback(Eegeo::Helpers::ICallback0& updateCallback)
            {
                m_updatedCallbacks.AddCallback(updateCallback);
            }

            void ReactionScreenOffsetProvider::RemoveOffsetUpdatedCallback(Eegeo::Helpers::ICallback0& updateCallback)
            {
                m_updatedCallbacks.RemoveCallback(updateCallback);
            }
        }
    }
}
