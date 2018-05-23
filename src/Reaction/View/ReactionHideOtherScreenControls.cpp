
#include "IIdentity.h"
#include "IReaction.h"
#include "IScreenControlViewModel.h"
#include "ReactionHideOtherScreenControls.h"
#include <vector>
#include <OpenableControl/View/IOpenableControlViewModel.h>

namespace ExampleApp
{
    namespace Reaction
    {
        namespace View
        {
            ReactionHideOtherScreenControls::ReactionHideOtherScreenControls(
                    const OpenableControl::View::IOpenableControlViewModel& openableControlViewModel,
                    const std::vector<ScreenControl::View::IScreenControlViewModel*>& screenControlsToHide)
                    : m_openableControl(openableControlViewModel)
                    , m_screenControlsToHide(screenControlsToHide)
            {

            }

            ReactionHideOtherScreenControls::ReactionHideOtherScreenControls(
                    const OpenableControl::View::IOpenableControlViewModel& openableControlViewModel,
                    ScreenControl::View::IScreenControlViewModel& screenControlToHide)
                    : m_openableControl(openableControlViewModel)
                    , m_screenControlsToHide({&screenControlToHide})
            {

            }

            Eegeo::Helpers::TIdentity ReactionHideOtherScreenControls::ReactionToOpenableIdentity()
            {
                return m_openableControl.GetIdentity();
            }

            void ReactionHideOtherScreenControls::Perform()
            {
                for(auto screenControl: m_screenControlsToHide){
                    if(screenControl->GetIdentity() != m_openableControl.GetIdentity()){
                        screenControl->UpdateOnScreenState(1.f-m_openableControl.OpenState());
                    }
                }
            }
        }
    }
}
