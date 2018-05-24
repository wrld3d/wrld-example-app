
#include "CallbackCollection.h"
#include "IReactionScreenOffsetProvider.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class ReactionScreenOffsetProvider : public IReactionScreenOffsetProvider
            {
                ScreenControl::View::IScreenControlViewPosition m_offset;
                Eegeo::Helpers::CallbackCollection0 m_updatedCallbacks;
            public:
                void SetOffset(ScreenControl::View::IScreenControlViewPosition offset);

                ScreenControl::View::IScreenControlViewPosition GetOffset() const override;

                void InsertOffsetUpdatedCallback(Eegeo::Helpers::ICallback0& updateCallback) override;

                void RemoveOffsetUpdatedCallback(Eegeo::Helpers::ICallback0& updateCallback) override;
            };
        }
    }
}
