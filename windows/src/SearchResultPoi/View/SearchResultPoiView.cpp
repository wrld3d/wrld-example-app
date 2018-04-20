// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiController.h"
#include "SearchResultPoiView.h"
#include "SearchVendorNames.h"
#include "WindowsAppThreadAssertionMacros.h"
#include "SearchResultModelCLI.h"
#include "ReflectionHelpers.h"
#include "SwallowSearchConstants.h"
#include "SwallowSearchParser.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            namespace
            {
                const std::string VendorViewClassNames[] = {
                    "ExampleAppWPF.YelpSearchResultsPoiView",
                    "ExampleAppWPF.eeGeoSearchResultsPoiView",
                    "ExampleAppWPF.SwallowWorkingGroupSearchResultsPoiView",
                    "ExampleAppWPF.SwallowPersonSearchResultsPoiView",
                    "ExampleAppWPF.SwallowMeetingRoomSearchResultsPoiView",
                    "ExampleAppWPF.SwallowFacilitySearchResultsPoiView",
                    "ExampleAppWPF.GeoNamesSearchResultsPoiView",
                    "ExampleAppWPF.SwallowDepartmentSearchResultsPoiView"
                };

                std::string personReadableTag;
            }

            SearchResultPoiView::SearchResultPoiView(WindowsNativeState& nativeState, const ExampleApp::Search::SdkModel::SearchTags& swallowSearchTags, bool isInKioskMode)
                : m_nativeState(nativeState)
                , m_currentVendor(-1)
                , m_isAnyPoiOpen(false)
            {
                personReadableTag = swallowSearchTags.defaultReadableTag;
                const std::vector<ExampleApp::Search::SdkModel::SearchTag>& tags = swallowSearchTags.tags;
                for(int i = 0; i < tags.size(); ++i)
                {
                    if(tags[i].tag == ExampleApp::Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME)
                    {
                        personReadableTag = tags[i].readableTag;
                        break;
                    }
                }

                for (int i = 0; i < SearchVendors::Num; ++i)
                {
                    m_uiViewClass[i] = GetTypeFromEntryAssembly(Helpers::ReflectionHelpers::ConvertUTF8ToManagedString(VendorViewClassNames[i]));

					ConstructorInfo^ ctor = m_uiViewClass[i]->GetConstructor(CreateTypes(IntPtr::typeid, System::Boolean::typeid));
					m_uiView[i] = ctor->Invoke(CreateObjects(gcnew IntPtr(this), gcnew System::Boolean(isInKioskMode)));

                    DisplayPoiInfo[i].SetupMethod(m_uiViewClass[i], m_uiView[i], "DisplayPoiInfo");
                    DismissPoiInfo[i].SetupMethod(m_uiViewClass[i], m_uiView[i], "DismissPoiInfo");
                    UpdateImageData[i].SetupMethod(m_uiViewClass[i], m_uiView[i], "UpdateImageData");
                    Destroy[i].SetupMethod(m_uiViewClass[i], m_uiView[i], "Destroy");
                }
            }

            SearchResultPoiView::~SearchResultPoiView()
            {
				for (int i = 0; i < SearchVendors::Num; ++i)
				{
					Destroy[i]();
				}
            }

            void SearchResultPoiView::Show(const Search::SdkModel::SearchResultModel& model, bool isPinned)
            {
                int previousVendor = m_currentVendor;

                m_model = model;
                CreateVendorSpecificPoiView(m_model.GetVendor(), m_model.GetPrimaryTag());

                if (m_isAnyPoiOpen && previousVendor != m_currentVendor && previousVendor != -1)
                {
                    DismissPoiInfo[previousVendor]();
                }
                
                if(m_currentVendor != -1)
                {
                    if (m_model.GetPrimaryTag() == ExampleApp::Search::Swallow::SearchConstants::DESK_CATEGORY_NAME)
                    {
                        const std::vector<std::string>& tagVector = m_model.GetTags();
                        std::vector<std::string> tagReadableVector = m_model.GetHumanReadableTags();

                        for(int i = 0; i < tagVector.size(); ++i)
                        {
                            if(tagVector[i] == ExampleApp::Search::Swallow::SearchConstants::DESK_CATEGORY_NAME)
                            {
                                tagReadableVector[i] = personReadableTag;
                            }
                        }

                        ExampleApp::Search::Swallow::SdkModel::SwallowPersonResultModel personModel = ExampleApp::Search::Swallow::SdkModel::SearchParser::TransformToSwallowPersonResult(m_model);

                        m_model = Search::SdkModel::SearchResultModel(m_model.CurrentVersion,
                            m_model.GetIdentifier(),
                            personModel.GetName(),
                            personModel.GetJobTitle(),
                            m_model.GetLocation(),
                            m_model.GetHeightAboveTerrainMetres(),
                            m_model.IsInterior(),
                            m_model.GetBuildingId(),
                            m_model.GetFloor(),
                            tagVector,
                            tagReadableVector,
                            ExampleApp::Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME,
                            m_model.GetVendor(),
                            m_model.GetJsonData(),
                            m_model.GetCreationTimestamp());
                    }

				    DisplayPoiInfo[m_currentVendor](gcnew SearchResultModelCLI(m_model));

                    m_isAnyPoiOpen = true;
                }
            }

            void SearchResultPoiView::Hide()
            {
                if(m_currentVendor != -1)
                {
                    DismissPoiInfo[m_currentVendor]();
                }

                m_isAnyPoiOpen = false;
            }

            void SearchResultPoiView::UpdateImage(const std::string& url, bool hasImage, const std::vector<unsigned char>* pImageBytes)
            {
                if (!hasImage || pImageBytes->empty())
                {
                    return;
                }
                
                array<System::Byte>^ imageDataArray = gcnew array<System::Byte>(static_cast<int>(pImageBytes->size()));

                for (size_t i = 0; i < pImageBytes->size(); ++i)
                {
                    imageDataArray[static_cast<int>(i)] = System::Byte(pImageBytes->at(i));
                }

                UpdateImageData[m_currentVendor](gcnew System::String(url.c_str()), System::Boolean(hasImage), imageDataArray);
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

                if(vendor == Search::YelpVendorName)
                {
                    m_currentVendor = SearchVendors::Yelp;
                }
                else if(vendor == Search::GeoNamesVendorName)
                {
                    m_currentVendor = SearchVendors::GeoNames;
                }
				else if (vendor == ExampleApp::Search::EegeoVendorName && (category == ExampleApp::Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME)
                    || category == ExampleApp::Search::Swallow::SearchConstants::DESK_CATEGORY_NAME)
				{
                    m_currentVendor = SearchVendors::SwallowPerson;
				}
				else if (vendor == ExampleApp::Search::EegeoVendorName
                    && (category == ExampleApp::Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME
                        || category == ExampleApp::Search::Swallow::SearchConstants::TRAINING_ROOM_CATEGORY_NAME))
				{
                    m_currentVendor = SearchVendors::SwallowMeetingRoom;
				}
				else if (vendor == ExampleApp::Search::EegeoVendorName && category == ExampleApp::Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME)
				{
                    m_currentVendor = SearchVendors::SwallowWorkingGroup;
				}
				else if (vendor == ExampleApp::Search::EegeoVendorName && (category == ExampleApp::Search::Swallow::SearchConstants::PRINT_STATION_CATEGORY_NAME
					|| category == ExampleApp::Search::Swallow::SearchConstants::TOILETS_CATEGORY_NAME
					|| category == ExampleApp::Search::Swallow::SearchConstants::FACILITY_CATEGORY_NAME
					|| category == ExampleApp::Search::Swallow::SearchConstants::EMERGENCY_EXIT_CATEGORY_NAME
					|| category == ExampleApp::Search::Swallow::SearchConstants::STATIONERY_CATEGORY_NAME)
                    || category == ExampleApp::Search::Swallow::SearchConstants::SHOW_POI_CARD_NAME)
				{
                    m_currentVendor = SearchVendors::SwallowFacility;
				}
				else if (vendor == ExampleApp::Search::EegeoVendorName && category == ExampleApp::Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME)
				{
                    m_currentVendor = SearchVendors::SwallowDepartment;
				}
                else
                {
                    m_currentVendor = -1;
                }
            }
        }
    }
}
