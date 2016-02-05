// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiController.h"
#include "SearchResultPoiView.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "SearchResultModelCLI.h"
#include "ReflectionHelpers.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiView::SearchResultPoiView(WindowsNativeState& nativeState)
                : m_nativeState(nativeState)
            {
            }

            SearchResultPoiView::~SearchResultPoiView()
            {
            }

            void SearchResultPoiView::Show(const Search::SdkModel::SearchResultModel model, bool isPinned)
            {
                m_model = model;
                CreateVendorSpecificPoiView(m_model.GetVendor());

				DisplayPoiInfo(gcnew SearchResultModelCLI(m_model), isPinned);
            }

            void SearchResultPoiView::Hide()
            {
                DismissPoiInfo();
            }

            void SearchResultPoiView::UpdateImage(const std::string& url, bool hasImage, const std::vector<unsigned char>* pImageBytes)
            {
                array<System::Byte>^ imageDataArray = gcnew array<System::Byte>(static_cast<int>(pImageBytes->size()));

                for (size_t i = 0; i < pImageBytes->size(); ++i)
                {
                    imageDataArray[static_cast<int>(i)] = System::Byte(pImageBytes->at(i));
                }

                UpdateImageData(gcnew System::String(url.c_str()), hasImage, imageDataArray);
            }

            void SearchResultPoiView::InsertClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_closedCallbacks.AddCallback(callback);
            }

            void SearchResultPoiView::RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.RemoveCallback(callback);
            }

            void SearchResultPoiView::HandleCloseClicked()
            {
                m_closedCallbacks.ExecuteCallbacks();
            }

            void SearchResultPoiView::InsertTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback)
            {
                ASSERT_UI_THREAD

                m_togglePinClickedCallbacks.AddCallback(callback);
            }

            void SearchResultPoiView::RemoveTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback)
            {
                ASSERT_UI_THREAD

                m_togglePinClickedCallbacks.RemoveCallback(callback);
            }

            void SearchResultPoiView::HandlePinToggleClicked()
            {
                ASSERT_UI_THREAD

                m_togglePinClickedCallbacks.ExecuteCallbacks(m_model);
            }

            void SearchResultPoiView::CreateVendorSpecificPoiView(const std::string& vendor)
            {
                ASSERT_UI_THREAD

				std::string viewClassName = "";

                if(vendor == "Yelp")
                {
					viewClassName = "ExampleAppWPF.YelpSearchResultsPoiView";
                }
                else if(vendor == "GeoNames")
                {
					viewClassName = "ExampleAppWPF.GeoNamesSearchResultsPoiView";
                }
                else
                {
                    Eegeo_ASSERT(false, "Unknown POI vendor %s, cannot create view instance.\n", vendor.c_str());
                }

				m_uiViewClass = GetTypeFromEntryAssembly(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(viewClassName));
				ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
				m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

				DisplayPoiInfo.SetupMethod(m_uiViewClass, m_uiView, "DisplayPoiInfo");
				DismissPoiInfo.SetupMethod(m_uiViewClass, m_uiView, "DismissPoiInfo");
				UpdateImageData.SetupMethod(m_uiViewClass, m_uiView, "UpdateImageData");
            }
        }
    }
}
