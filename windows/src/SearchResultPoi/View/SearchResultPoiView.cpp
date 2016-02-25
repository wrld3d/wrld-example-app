// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiController.h"
#include "SearchResultPoiView.h"
#include "SearchVendorNames.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "SearchResultModelCLI.h"
#include "ReflectionHelpers.h"
#include "SwallowSearchConstants.h"

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
                CreateVendorSpecificPoiView(m_model.GetVendor(), m_model.GetCategory());

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

			void SearchResultPoiView::InsertAvailabilityChangedCallback(Eegeo::Helpers::ICallback2<const Search::SdkModel::SearchResultModel&, const std::string&>& callback)
			{
				m_availabilityChangedCallbacks.AddCallback(callback);
			}

			void SearchResultPoiView::RemoveAvailabilityChangedCallback(Eegeo::Helpers::ICallback2<const Search::SdkModel::SearchResultModel&, const std::string&>& callback)
			{
				m_availabilityChangedCallbacks.RemoveCallback(callback);
			}

			void SearchResultPoiView::HandleAvailabilityChanged(const std::string& availability)
			{
				m_availabilityChangedCallbacks.ExecuteCallbacks(m_model, availability);
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

            void SearchResultPoiView::CreateVendorSpecificPoiView(const std::string& vendor, const std::string& category)
            {
                ASSERT_UI_THREAD
				
                std::string viewClassName = "";
				
                if(vendor == ExampleApp::Search::YelpVendorName)
                {
					viewClassName = "ExampleAppWPF.YelpSearchResultsPoiView";
                }
                else if(vendor == ExampleApp::Search::GeoNamesVendorName)
                {
					viewClassName = "ExampleAppWPF.GeoNamesSearchResultsPoiView";
                }
				else if (vendor == ExampleApp::Search::EegeoVendorName && category == ExampleApp::Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME)
				{
					viewClassName = "ExampleAppWPF.SwallowPersonSearchResultsPoiView";
				}
				else if (vendor == ExampleApp::Search::EegeoVendorName && category == ExampleApp::Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
				{
					viewClassName = "ExampleAppWPF.SwallowMeetingRoomSearchResultsPoiView";
				}
				else if (vendor == ExampleApp::Search::EegeoVendorName && category == ExampleApp::Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME)
				{
					viewClassName = "ExampleAppWPF.SwallowWorkingGroupSearchResultsPoiView";
				}
				else if (vendor == ExampleApp::Search::EegeoVendorName && (category == ExampleApp::Search::Swallow::SearchConstants::PRINT_STATION_CATEGORY_NAME
					|| category == ExampleApp::Search::Swallow::SearchConstants::TOILETS_CATEGORY_NAME
					|| category == ExampleApp::Search::Swallow::SearchConstants::FACILITY_CATEGORY_NAME
					|| category == ExampleApp::Search::Swallow::SearchConstants::EMERGENCY_EXIT_CATEGORY_NAME
					|| category == ExampleApp::Search::Swallow::SearchConstants::STATIONERY_CATEGORY_NAME))
				{
					viewClassName = "ExampleAppWPF.SwallowFacilitySearchResultsPoiView";
				}
				else if (vendor == ExampleApp::Search::EegeoVendorName && category == ExampleApp::Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME)
				{
					viewClassName = "ExampleAppWPF.SwallowDepartmentSearchResultsPoiView";
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
