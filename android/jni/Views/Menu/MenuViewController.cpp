// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include "MenuViewController.h"
#include "Types.h"
#include "MenuItemModel.h"
#include "IMenuViewModel.h"
#include "IMenuModel.h"
#include "ICallback.h"
#include "IMenuSectionViewModel.h"
#include "Logger.h"
#include "AndroidAppThreadAssertionMacros.h"

#define MenuViewController_TTY EXAMPLE_LOG
//#define MenuViewController_TTY(...)

namespace ExampleApp
{
	namespace Menu
	{
		MenuViewController::MenuViewController(
		    const std::string& viewClassName,
		    AndroidNativeState& nativeState,
		    ExampleApp::Menu::IMenuModel& menuModel,
		    ExampleApp::Menu::IMenuViewModel& menuViewModel
		)
			: m_nativeState(nativeState)
			, m_menuModel(menuModel)
			, m_menuViewModel(menuViewModel)
			, m_pMenuAddedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<MenuViewController, MenuItemModel>))(this, &MenuViewController::ItemAddedCallback))
			, m_pMenuRemovedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback1<MenuViewController, MenuItemModel>))(this, &MenuViewController::ItemRemovedCallback))
			, m_pOpenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<MenuViewController, OpenableControlViewModel::IOpenableControlViewModel&, float>))(this, &MenuViewController::OpenStateChangedCallback))
			, m_pOnScreenStateChangedCallback(Eegeo_NEW((Eegeo::Helpers::TCallback2<MenuViewController, ScreenControlViewModel::IScreenControlViewModel&, float>))(this, &MenuViewController::OnScreenStateChangedCallback))
			, m_dragInProgress(false)
			, m_presentationDirty(false)
		{
			ASSERT_UI_THREAD

			m_menuModel.InsertItemAddedCallback(*m_pMenuAddedCallback);
			m_menuModel.InsertItemRemovedCallback(*m_pMenuRemovedCallback);

			m_menuViewModel.InsertOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
			m_menuViewModel.InsertOpenStateChangedCallback(*m_pOpenStateChangedCallback);

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jstring strClassName = env->NewStringUTF(viewClassName.c_str());
			jclass uiClass = m_nativeState.LoadClass(env, strClassName);
			env->DeleteLocalRef(strClassName);

			m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
			env->DeleteLocalRef(uiClass);
			jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/mobileexampleapp/MainActivity;J)V");

			jobject instance = env->NewObject(
			                       m_uiViewClass,
			                       uiViewCtor,
			                       m_nativeState.activity,
			                       (jlong)(this)
			                   );

			m_uiView = env->NewGlobalRef(instance);
			env->DeleteLocalRef(instance);

			if(m_menuViewModel.IsFullyOnScreen())
			{
				float value = m_menuViewModel.OpenState();
				OpenStateChangedCallback(m_menuViewModel, value);
			}

			m_presentationDirty = true;
		}

		MenuViewController::~MenuViewController()
		{
			ASSERT_UI_THREAD

			m_menuModel.RemoveItemAddedCallback(*m_pMenuAddedCallback);
			m_menuModel.RemoveItemRemovedCallback(*m_pMenuRemovedCallback);

			Eegeo_DELETE m_pMenuAddedCallback;
			Eegeo_DELETE m_pMenuRemovedCallback;

			m_menuViewModel.RemoveOnScreenStateChangedCallback(*m_pOnScreenStateChangedCallback);
			m_menuViewModel.RemoveOpenStateChangedCallback(*m_pOpenStateChangedCallback);

			Eegeo_DELETE m_pOnScreenStateChangedCallback;
			Eegeo_DELETE m_pOpenStateChangedCallback;

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;
			jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
			env->CallVoidMethod(m_uiView, removeHudMethod);
			env->DeleteGlobalRef(m_uiView);
			env->DeleteGlobalRef(m_uiViewClass);
		}

		void MenuViewController::UpdateUiThread(float deltaSeconds)
		{
			ASSERT_UI_THREAD

			if(m_presentationDirty)
			{
				RefreshPresentation();
			}

			if(m_dragInProgress)
			{
				return;
			}

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			static jmethodID isAnimatingMethod = env->GetMethodID(m_uiViewClass, "isAnimating", "()Z");
			const bool isAnimating = env->CallBooleanMethod(m_uiView, isAnimatingMethod);

			if(isAnimating)
			{
				static jmethodID updateAnimationMethod = env->GetMethodID(m_uiViewClass, "updateAnimation", "(F)V");
				env->CallVoidMethod(m_uiView, updateAnimationMethod, deltaSeconds);

				if(m_menuViewModel.HasReactorControl())
				{
					static jmethodID normalisedAnimationProgressMethod = env->GetMethodID(m_uiViewClass, "normalisedAnimationProgress", "()F");
					const float normalisedAnimationProgress = env->CallFloatMethod(m_uiView, normalisedAnimationProgressMethod);
					MenuViewController_TTY("Normalised animation progress: %f\n", normalisedAnimationProgress);
					m_menuViewModel.UpdateOpenState(normalisedAnimationProgress);
				}
			}
		}

		void MenuViewController::HandleViewOpenCompleted()
		{
			ASSERT_UI_THREAD

			Eegeo_ASSERT(!m_dragInProgress, "identity %d\n", Identity());

			if(!m_menuViewModel.IsFullyOpen())
			{
				MenuViewController_TTY("ReleaseReactorControl -- HandleViewOpenCompleted\n");
				m_menuViewModel.Open();
			}

			if(m_menuViewModel.HasReactorControl())
			{
				MenuViewController_TTY("ReleaseReactorControl -- HandleViewOpenCompleted\n");
				m_menuViewModel.ReleaseReactorControl();
			}
		}

		void MenuViewController::HandleViewCloseCompleted()
		{
			ASSERT_UI_THREAD

			Eegeo_ASSERT(!m_dragInProgress, "identity %d\n", Identity());

			if(!m_menuViewModel.IsFullyClosed())
			{
				MenuViewController_TTY("ReleaseReactorControl -- HandleViewCloseCompleted\n");
				m_menuViewModel.Close();
			}

			if(m_menuViewModel.HasReactorControl())
			{
				MenuViewController_TTY("ReleaseReactorControl -- HandleViewCloseCompleted\n");
				m_menuViewModel.ReleaseReactorControl();
			}
		}

		Eegeo::Helpers::TIdentity MenuViewController::Identity() const
		{
			ASSERT_UI_THREAD

			return static_cast<OpenableControlViewModel::IOpenableControlViewModel&>(m_menuViewModel).GetIdentity();
		}

		void MenuViewController::HandleViewClicked()
		{
			ASSERT_UI_THREAD

			MenuViewController_TTY("MenuViewController::HandleViewClicked -- %d\n", Identity());
			if(!m_menuViewModel.TryAcquireReactorControl())
			{
				MenuViewController_TTY("MenuViewController::HandleViewClicked -- reactor denied for %d!\n", Identity());
				return;
			}

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			if(m_menuViewModel.IsFullyClosed())
			{
				jmethodID animateToOpenOnScreen = env->GetMethodID(m_uiViewClass, "animateToOpenOnScreen", "()V");
				env->CallVoidMethod(m_uiView, animateToOpenOnScreen);
			}
			else if(m_menuViewModel.IsFullyOpen())
			{
				jmethodID animateToClosedOnScreen = env->GetMethodID(m_uiViewClass, "animateToClosedOnScreen", "()V");
				env->CallVoidMethod(m_uiView, animateToClosedOnScreen);
			}
			else
			{
				MenuViewController_TTY("ReleaseReactorControl -- HandleViewClicked\n");
				m_menuViewModel.ReleaseReactorControl();
			}
		}

		bool MenuViewController::TryBeginDrag()
		{
			ASSERT_UI_THREAD

			if(m_menuViewModel.TryAcquireReactorControl())
			{
				MenuViewController_TTY("MenuViewController::TryBeginDrag -- reactor granted for %d!\n", Identity());
				return true;
			}

			MenuViewController_TTY("MenuViewController::TryBeginDrag -- reactor denied for %d!\n", Identity());
			return false;
		}

		void MenuViewController::HandleDraggingViewStarted()
		{
			ASSERT_UI_THREAD

			Eegeo_ASSERT(!m_dragInProgress, "identity %d\n", Identity());

			{
				const bool acquiredReactorControl = m_menuViewModel.TryAcquireReactorControl();
				Eegeo_ASSERT(acquiredReactorControl, "%d failed to acquire reactor control.\n", Identity());
			}

			m_dragInProgress = true;
		}

		void MenuViewController::HandleDraggingViewInProgress(float normalisedDragState)
		{
			ASSERT_UI_THREAD

			Eegeo_ASSERT(m_dragInProgress);

			{
				const bool acquiredReactorControl = m_menuViewModel.TryAcquireReactorControl();
				Eegeo_ASSERT(acquiredReactorControl, "%d failed to acquire reactor control.\n", Identity());
			}

			m_menuViewModel.UpdateOpenState(normalisedDragState);
		}

		void MenuViewController::HandleDraggingViewCompleted()
		{
			ASSERT_UI_THREAD

			Eegeo_ASSERT(m_dragInProgress);

			{
				const bool acquiredReactorControl = m_menuViewModel.TryAcquireReactorControl();
				Eegeo_ASSERT(acquiredReactorControl, "%d failed to acquire reactor control.\n", Identity());
			}

			m_dragInProgress = false;
		}

		void MenuViewController::ItemAddedCallback(ExampleApp::Menu::MenuItemModel& item)
		{
			ASSERT_UI_THREAD

			m_presentationDirty = true;
		}

		void MenuViewController::ItemRemovedCallback(ExampleApp::Menu::MenuItemModel& item)
		{
			ASSERT_UI_THREAD

			m_presentationDirty = true;
		}

		void MenuViewController::OnScreenStateChangedCallback(ScreenControlViewModel::IScreenControlViewModel& viewModel, float& onScreenState)
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			if(m_menuViewModel.IsFullyOnScreen())
			{
				jmethodID animateToClosedOnScreen = env->GetMethodID(m_uiViewClass, "animateToClosedOnScreen", "()V");
				env->CallVoidMethod(m_uiView, animateToClosedOnScreen);
			}
			else if (m_menuViewModel.IsFullyOffScreen())
			{
				jmethodID animateOffScreen = env->GetMethodID(m_uiViewClass, "animateOffScreen", "()V");
				env->CallVoidMethod(m_uiView, animateOffScreen);
			}
			else
			{
				jmethodID animateToIntermediateOpenStateOnScreen = env->GetMethodID(m_uiViewClass, "animateToIntermediateOnScreenState", "(F)V");
				env->CallVoidMethod(m_uiView, animateToIntermediateOpenStateOnScreen, onScreenState);
			}
		}

		void MenuViewController::OpenStateChangedCallback(OpenableControlViewModel::IOpenableControlViewModel& viewModel, float& openState)
		{
			ASSERT_UI_THREAD

			if(m_dragInProgress)
			{
				return;
			}

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			if(m_menuViewModel.IsFullyClosed())
			{
				jmethodID animateToClosedOnScreen = env->GetMethodID(m_uiViewClass, "animateToClosedOnScreen", "()V");
				env->CallVoidMethod(m_uiView, animateToClosedOnScreen);
			}
			else if(m_menuViewModel.IsFullyOpen())
			{
				jmethodID animateToOpenOnScreen = env->GetMethodID(m_uiViewClass, "animateToOpenOnScreen", "()V");
				env->CallVoidMethod(m_uiView, animateToOpenOnScreen);
			}
			else
			{
				jmethodID animateToIntermediateOpenStateOnScreen = env->GetMethodID(m_uiViewClass, "animateToIntermediateOpenState", "(F)V");
				env->CallVoidMethod(m_uiView, animateToIntermediateOpenStateOnScreen, openState);
			}
		}

		void MenuViewController::HandleItemSelected(const std::string& selection, const int index)
		{
			ASSERT_UI_THREAD

			const size_t numSections = m_menuViewModel.SectionsCount();
			int currentIndex = 0;
			for(size_t i = 0; i < numSections; ++ i)
			{
				Menu::IMenuSectionViewModel& section = m_menuViewModel.GetMenuSection(i);
				const size_t numItemsInSection = section.Size();

				for(size_t j = 0; j < numItemsInSection; ++ j)
				{
					if(currentIndex == index)
					{
						if(section.IsExpandable() && j == 0)
						{
							if(section.IsExpanded())
							{
								section.Contract();
							}
							else
							{
								section.Expand();
							}
							m_presentationDirty = true;
							return;
						}
						else
						{
							int itemIndex = section.IsExpandable() ? j - 1 : j;
							ExampleApp::Menu::MenuItemModel item = section.GetItemAtIndex(itemIndex);

							item.Select();

							return;
						}
					}
					currentIndex++;
				}
			}
		}

		void MenuViewController::RefreshPresentation()
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jstring strClassName = env->NewStringUTF("java/lang/String");
			jclass strClass = m_nativeState.LoadClass(env, strClassName);
			env->DeleteLocalRef(strClassName);

			const size_t numSections = m_menuViewModel.SectionsCount();
			size_t numItems = 0;
			for(size_t i = 0; i < numSections; ++ i)
			{
				const Menu::IMenuSectionViewModel& section = m_menuViewModel.GetMenuSection(i);
				numItems += section.Size();
			}

			jobjectArray groupNamesArray = env->NewObjectArray(numSections, strClass, 0);
			jintArray groupSizesArray = env->NewIntArray(numSections);
			jbooleanArray groupIsExpandableArray = env->NewBooleanArray(numSections);
			jobjectArray childNamesArray = env->NewObjectArray(numItems, strClass, 0);
			env->DeleteLocalRef(strClass);

			size_t currentChildIndex = 0;
			for(size_t groupIndex = 0; groupIndex < numSections; groupIndex++)
			{
				const Menu::IMenuSectionViewModel& section = m_menuViewModel.GetMenuSection(groupIndex);
				for(size_t childIndex = 0; childIndex < section.Size(); childIndex++)
				{
					int itemIndex = section.IsExpandable() ? childIndex-1 : childIndex;
					std::string jsonData = section.IsExpandable() && childIndex == 0
					                       ? section.SerializeJson()
					                       : section.GetItemAtIndex(itemIndex).SerializeJson();
					jstring jsonDataStr = env->NewStringUTF(jsonData.c_str());
					env->SetObjectArrayElement(childNamesArray, currentChildIndex, jsonDataStr);
					env->DeleteLocalRef(jsonDataStr);
					currentChildIndex++;
				}

				jstring groupNameJni = env->NewStringUTF(section.Name().c_str());
				env->SetObjectArrayElement(groupNamesArray, groupIndex, groupNameJni);
				env->DeleteLocalRef(groupNameJni);

				jint groupSize = (jint)(section.Size());
				env->SetIntArrayRegion(groupSizesArray, groupIndex, 1, &groupSize);

				jboolean groupIsExpandable = (jboolean)(section.IsExpandable());
				env->SetBooleanArrayRegion(groupIsExpandableArray, groupIndex, 1, &groupIsExpandable);
			}

			jmethodID populateData = env->GetMethodID(m_uiViewClass, "populateData", "(J[Ljava/lang/String;[I[Z[Ljava/lang/String;)V");

			env->CallVoidMethod(
			    m_uiView,
			    populateData,
			    (jlong)(this),
			    groupNamesArray,
			    groupSizesArray,
			    groupIsExpandableArray,
			    childNamesArray
			);

			env->DeleteLocalRef(groupNamesArray);
			env->DeleteLocalRef(groupSizesArray);
			env->DeleteLocalRef(childNamesArray);
			env->DeleteLocalRef(groupIsExpandableArray);

			m_presentationDirty = false;
		}
	}
}

#undef MenuViewController_TTY
