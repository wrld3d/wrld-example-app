// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsView.h"
#include "MyPinDetailsViewImpl.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsView::MyPinDetailsView(const std::shared_ptr<WindowsNativeState>& nativeState)
            {
                m_pImpl = Eegeo_NEW(MyPinDetailsViewImpl)(nativeState);
            }

            MyPinDetailsView::~MyPinDetailsView()
            {
                Eegeo_DELETE m_pImpl;
            }

            void MyPinDetailsView::OnDismiss()
            {
                m_pImpl->OnDismiss();
            }

            void MyPinDetailsView::OnRemove()
            {
                m_pImpl->OnRemove();
            }

            void MyPinDetailsView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertDismissedCallback(callback);
            }

            void MyPinDetailsView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveDismissedCallback(callback);
            }

            void MyPinDetailsView::InsertRemovePinCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->InsertRemovePinCallback(callback);
            }

            void MyPinDetailsView::RemoveRemovePinCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_pImpl->RemoveRemovePinCallback(callback);
            }

            void MyPinDetailsView::OpenWithModel(
                    const std::string& title,
                    const std::string& description,
                    const std::string& imagePath)
            {
                m_pImpl->OpenWithModel(title, description, imagePath);
            }

            void MyPinDetailsView::Close()
            {
                m_pImpl->Close();
            }
        }
    }
}
