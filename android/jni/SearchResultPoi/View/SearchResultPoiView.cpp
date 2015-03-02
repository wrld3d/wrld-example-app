// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiView.h"
#include "AndroidAppThreadAssertionMacros.h"

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

            void SearchResultPoiView::Show(const Search::SdkModel::SearchResultModel model, bool isPinned)
            {
                ASSERT_UI_THREAD

                m_model = model;
                CreateVendorSpecificPoiView(m_model.GetVendor());

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                const std::vector<std::string>& humanReadableCategories(model.GetHumanReadableCategories());

                jobjectArray humanReadableCategoriesArray = env->NewObjectArray(
                	humanReadableCategories.size(),
					env->FindClass("java/lang/String"),
					0
                );

                for(size_t i = 0; i < humanReadableCategories.size(); ++ i)
                {
                	const std::string& categoryString(humanReadableCategories[i]);
                    jstring jniString = env->NewStringUTF(categoryString.c_str());
                    env->SetObjectArrayElement(humanReadableCategoriesArray, i, jniString);
                    env->DeleteLocalRef(jniString);
                }

                const std::vector<std::string>& reviews(model.GetReviews());

                jobjectArray reviewsArray = env->NewObjectArray(
                	reviews.size(),
					env->FindClass("java/lang/String"),
					0
                );

                for(size_t i = 0; i < reviews.size(); ++ i)
                {
                	const std::string& reviewString(reviews[i]);
                    jstring jniString = env->NewStringUTF(reviewString.c_str());
                    env->SetObjectArrayElement(reviewsArray, i, jniString);
                    env->DeleteLocalRef(jniString);
                }

                jstring titleStr = env->NewStringUTF(model.GetTitle().c_str());
                jstring addressStr = env->NewStringUTF(model.GetAddress().c_str());
                jstring phoneStr = env->NewStringUTF(model.GetPhone().c_str());
                jstring urlStr = env->NewStringUTF(model.GetWebUrl().c_str());
                jstring categoryStr = env->NewStringUTF(model.GetCategory().c_str());
                jstring imageUrlStr = env->NewStringUTF(model.GetImageUrl().c_str());
                jstring ratingImageUrlStr = env->NewStringUTF(model.GetRatingImageUrl().c_str());
                jstring vendorStr = env->NewStringUTF(model.GetVendor().c_str());

                jmethodID displayPoiInfoMethod = env->GetMethodID(m_uiViewClass, "displayPoiInfo", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Z)V");
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

            void SearchResultPoiView::CreateVendorSpecificPoiView(const std::string& vendor)
            {
                ASSERT_UI_THREAD

                std::string viewClass = "";

                if(vendor == "Yelp")
                {
                    viewClass = "com/eegeo/searchresultpoiview/YelpSearchResultPoiView";
                }
                else if(vendor == "DeCarta")
                {
                    viewClass = "com/eegeo/searchresultpoiview/DeCartaSearchResultPoiView";
                }
                else if(vendor == "GeoNames")
                {
                    viewClass = "com/eegeo/searchresultpoiview/GeoNamesSearchResultPoiView";
                }
                else
                {
                	Eegeo_ASSERT(false, "Unknown POI vendor %s, cannot create view instance.\n", vendor.c_str());
                }


                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF(viewClass.c_str());
                jclass uiClass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
                jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/mobileexampleapp/MainActivity;J)V");

                jobject instance = env->NewObject(
                                       m_uiViewClass,
                                       uiViewCtor,
                                       m_nativeState.activity,
                                       (jlong)(this)
                                   );

                m_uiView = env->NewGlobalRef(instance);
            }
        }
    }
}
