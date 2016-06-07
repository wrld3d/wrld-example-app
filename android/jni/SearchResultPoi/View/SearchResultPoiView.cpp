// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "SearchVendorNames.h"
#include "YelpSearchResultModel.h"
#include "YelpParsingHelpers.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiView::SearchResultPoiView(AndroidNativeState& nativeState)
                : m_nativeState(nativeState)
            	, m_uiViewClass(NULL)
                , m_uiView(NULL)
            {
                ASSERT_UI_THREAD
            }

            SearchResultPoiView::~SearchResultPoiView()
            {
                ASSERT_UI_THREAD
            }

            void SearchResultPoiView::Show(const Search::SdkModel::SearchResultModel& model, bool isPinned)
            {
                ASSERT_UI_THREAD

                m_model = model;
                const std::string& vendor = m_model.GetVendor();
                if(vendor == Search::YelpVendorName)
                {
                	CreateAndShowYelpPoiView(model, isPinned);
                }
                else if(vendor == Search::GeoNamesVendorName)
                {
                	CreateAndShowGeoNamesPoiView(model, isPinned);
                }
                else
                {
                	Eegeo_ASSERT(false, "Unknown POI vendor %s, cannot create view instance.\n", vendor.c_str());
                }

            }

            void SearchResultPoiView::Hide()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID dismissPoiInfo = env->GetMethodID(m_uiViewClass, "dismissPoiInfo", "()V");
                env->CallVoidMethod(m_uiView, dismissPoiInfo);

                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);

                m_uiViewClass = NULL;
                m_uiView = NULL;
            }

            void SearchResultPoiView::UpdateImage(const std::string& url, bool hasImage, const std::vector<Byte>* pImageBytes)
            {
                ASSERT_UI_THREAD

    			AndroidSafeNativeThreadAttachment attached(m_nativeState);
    			JNIEnv* env = attached.envForThread;

    			unsigned int imgSize = hasImage ? pImageBytes->size() : 0;
    			jbyteArray imgArr = env->NewByteArray(imgSize);
    			if(imgSize)
    			{
    				env->SetByteArrayRegion(imgArr,0,imgSize, (jbyte*)(&(pImageBytes->at(0))));
    			}
                jstring urlStr = env->NewStringUTF(url.c_str());

    			jmethodID updateImageData = env->GetMethodID(m_uiViewClass, "updateImageData", "(Ljava/lang/String;Z[B)V");
    			env->CallVoidMethod(m_uiView, updateImageData, urlStr, hasImage, imgArr);

                env->DeleteLocalRef(urlStr);
    			env->DeleteLocalRef(imgArr);
            }

            void SearchResultPoiView::InsertAvailabilityChangedCallback(Eegeo::Helpers::ICallback2<const Search::SdkModel::SearchResultModel&, const std::string&>& callback)
            {
            	// TJ: Stubbed for Droid implementation
            }

            void SearchResultPoiView::RemoveAvailabilityChangedCallback(Eegeo::Helpers::ICallback2<const Search::SdkModel::SearchResultModel&, const std::string&>& callback)
            {
            	// TJ: Stubbed for Droid implementation
            }

            void SearchResultPoiView::InsertClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.AddCallback(callback);
            }

            void SearchResultPoiView::RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.RemoveCallback(callback);
            }

            void SearchResultPoiView::HandleCloseClicked()
            {
                ASSERT_UI_THREAD

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

            void SearchResultPoiView::CreateAndShowYelpPoiView(const Search::SdkModel::SearchResultModel& model, bool isPinned)
            {
            	const std::string viewClass = "com/eegeo/searchresultpoiview/YelpSearchResultPoiView";
            	m_uiViewClass = CreateJavaClass(viewClass);
            	m_uiView = CreateJavaObject(m_uiViewClass);

            	Search::Yelp::SdkModel::YelpSearchResultModel yelpModel;
            	yelpModel = Search::Yelp::SdkModel::Helpers::TransformToYelpSearchResult(model);

            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
            	JNIEnv* env = attached.envForThread;

            	jobjectArray humanReadableCategoriesArray = CreateJavaArray(model.GetHumanReadableCategories());
            	jobjectArray reviewsArray = CreateJavaArray(yelpModel.GetReviews());

            	jstring titleStr = env->NewStringUTF(model.GetTitle().c_str());
            	jstring addressStr = env->NewStringUTF(model.GetSubtitle().c_str());
            	jstring phoneStr = env->NewStringUTF(yelpModel.GetPhone().c_str());
            	jstring urlStr = env->NewStringUTF(yelpModel.GetWebUrl().c_str());
            	jstring categoryStr = env->NewStringUTF(model.GetCategory().c_str());
            	jstring imageUrlStr = env->NewStringUTF(yelpModel.GetImageUrl().c_str());
            	jstring ratingImageUrlStr = env->NewStringUTF(yelpModel.GetRatingImageUrl().c_str());
            	jstring vendorStr = env->NewStringUTF(model.GetVendor().c_str());

            	jmethodID displayPoiInfoMethod = env->GetMethodID(m_uiViewClass, "displayPoiInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;IZ)V");
            	env->CallVoidMethod(
            			m_uiView,
						displayPoiInfoMethod,
						titleStr,
						addressStr,
						phoneStr,
						urlStr,
						categoryStr,
						humanReadableCategoriesArray,
						imageUrlStr,
						ratingImageUrlStr,
						vendorStr,
						reviewsArray,
						yelpModel.GetReviewCount(),
						isPinned
            	);

            	env->DeleteLocalRef(vendorStr);
            	env->DeleteLocalRef(ratingImageUrlStr);
            	env->DeleteLocalRef(imageUrlStr);
            	env->DeleteLocalRef(categoryStr);
            	env->DeleteLocalRef(urlStr);
            	env->DeleteLocalRef(phoneStr);
            	env->DeleteLocalRef(addressStr);
            	env->DeleteLocalRef(titleStr);
            	env->DeleteLocalRef(reviewsArray);
            	env->DeleteLocalRef(humanReadableCategoriesArray);
            }

            void SearchResultPoiView::CreateAndShowGeoNamesPoiView(const Search::SdkModel::SearchResultModel& model, bool isPinned)
            {
            	const std::string viewClass = "com/eegeo/searchresultpoiview/GeoNamesSearchResultPoiView";
            	m_uiViewClass = CreateJavaClass(viewClass);
            	m_uiView = CreateJavaObject(m_uiViewClass);

            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
            	JNIEnv* env = attached.envForThread;

            	jstring titleStr = env->NewStringUTF(model.GetTitle().c_str());
            	jstring addressStr = env->NewStringUTF(model.GetSubtitle().c_str());
            	jstring categoryStr = env->NewStringUTF(model.GetCategory().c_str());

            	jmethodID displayPoiInfoMethod = env->GetMethodID(m_uiViewClass, "displayPoiInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
            	env->CallVoidMethod(
            			m_uiView,
						displayPoiInfoMethod,
						titleStr,
						addressStr,
						categoryStr,
						isPinned
            	);

            	env->DeleteLocalRef(categoryStr);
            	env->DeleteLocalRef(addressStr);
            	env->DeleteLocalRef(titleStr);
            }

            jclass SearchResultPoiView::CreateJavaClass(const std::string& viewClass)
            {
            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
            	JNIEnv* env = attached.envForThread;

            	jstring strClassName = env->NewStringUTF(viewClass.c_str());
            	jclass uiClass = m_nativeState.LoadClass(env, strClassName);
            	env->DeleteLocalRef(strClassName);

            	return static_cast<jclass>(env->NewGlobalRef(uiClass));
            }

            jobject SearchResultPoiView::CreateJavaObject(jclass uiViewClass)
            {
            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
            	JNIEnv* env = attached.envForThread;

            	jmethodID uiViewCtor = env->GetMethodID(uiViewClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

            	jobject instance = env->NewObject(
            			uiViewClass,
						uiViewCtor,
						m_nativeState.activity,
						(jlong)(this)
            	);

            	return env->NewGlobalRef(instance);
            }

            jobjectArray SearchResultPoiView::CreateJavaArray(const std::vector<std::string>& stringVector)
            {
            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
            	JNIEnv* env = attached.envForThread;

            	jobjectArray jniStringArray = env->NewObjectArray(
            			stringVector.size(),
						env->FindClass("java/lang/String"),
						0
            	);

            	for(size_t i = 0; i < stringVector.size(); ++ i)
            	{
            		jstring jniString = env->NewStringUTF(stringVector[i].c_str());
            		env->SetObjectArrayElement(jniStringArray, i, jniString);
            		env->DeleteLocalRef(jniString);
            	}

            	return jniStringArray;
            }
        }
    }
}
