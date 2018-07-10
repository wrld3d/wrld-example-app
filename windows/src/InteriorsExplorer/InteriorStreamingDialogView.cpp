// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorStreamingDialogView.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            InteriorStreamingDialogView::InteriorStreamingDialogView()
            {

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mOpenInteriorStreamingDialogView.SetupMethod(m_uiViewClass, m_uiView, "OpenInteriorStreamingDialogView");
                mDismissInteriorStreamingDialogView.SetupMethod(m_uiViewClass, m_uiView, "DismissInteriorStreamingDialogView");
                mCancelInteriorStreamingDialogView.SetupMethod(m_uiViewClass, m_uiView, "CancelInteriorStreamingDialogView");
            }

            InteriorStreamingDialogView::~InteriorStreamingDialogView()
            {
                mDestroy();
            }

            void InteriorStreamingDialogView::Show()
            {
                // TODO: Implementation of windows view
            }

            void InteriorStreamingDialogView::Hide(bool interiorLoaded)
            {
                if (interiorLoaded)
                {
                    mDismissInteriorStreamingDialogView();
                }
                else
                {
                    mCancelInteriorStreamingDialogView();
                }
            }
        }
    }
}