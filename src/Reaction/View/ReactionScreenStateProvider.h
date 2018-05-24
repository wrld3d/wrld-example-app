
#include "CallbackCollection.h"
#include "IReactionScreenStateProvider.h"

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            class ReactionScreenStateProvider : public IReactionScreenStateProvider
            {
                ScreenControl::View::TScreenControlViewState m_state;
                Eegeo::Helpers::CallbackCollection0 m_updatedCallbacks;
            public:
                void SetState(ScreenControl::View::TScreenControlViewState state);

                ScreenControl::View::TScreenControlViewState GetState() const override;

                void InsertStateUpdatedCallback(Eegeo::Helpers::ICallback0 &updateCallback) override;

                void RemoveStateUpdatedCallback(Eegeo::Helpers::ICallback0 &updateCallback) override;
            };
        }
    }
}
