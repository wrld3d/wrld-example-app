// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorStreamingDialogView.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            InteriorStreamingDialogView::InteriorStreamingDialogView(WindowsNativeState& nativeState)
                : m_nativeState(nativeState)
            {
                m_uiViewClass = Helpers::ReflectionHelpers::GetTypeFromEntryAssembly("ExampleAppWPF.InteriorStreamingDialogView");
                System::Reflection::ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(Helpers::ReflectionHelpers::CreateTypes(System::IntPtr::typeid));
                m_uiView = ctor->Invoke(Helpers::ReflectionHelpers::CreateObjects(gcnew System::IntPtr(this)));

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
                mOpenInteriorStreamingDialogView();
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