// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchWidgetView.h"
#include "WidgetSearchResultModel.h"
#include "TagCollection.h"
#include "IScreenControlView.h"
#include "ISearchNavigationHandler.h"
#import <WrldSearchWidget/WrldSearchWidget.h>

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchWidgetView : public SearchMenu::View::ISearchWidgetView, public ISearchNavigationHandler
            {
            private:
                WRLDSearchWidgetView* m_pSearchWidgetView;
                WRLDSearchModel* m_pSearchModel;
                WRLDSearchMenuModel* m_pMenuModel;
                WRLDSearchProviderHandle* m_pSearchProviderHandle;
                WRLDSuggestionProviderHandle* m_pSuggestionProviderHandle;
                WRLDSpeechCapture* m_pSpeechCapture;

                Eegeo::Helpers::CallbackCollection0 m_searchClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<int> m_resultSelectedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const std::string&> m_searchbarTextChangedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const int> m_navigationRequestedCallbacks;
                Eegeo::Helpers::CallbackCollection3<const std::string&, int, int> m_onItemSelectedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewOpenedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewClosedCallbacks;
                
                NSMutableDictionary* m_pMenuGroups;
                NSMutableDictionary* m_pMenuOptions;
                
                bool m_hasPopulatedData;
                
                void (^m_onResultSelection) (id<WRLDSearchResultModel>);
                void (^m_willPopulateResultCell) (WRLDSearchResultTableViewCell*);
                void (^m_onMenuSelection) (NSObject*);
                void (^m_onResultsReceived) ();
                void (^m_onResultsCleared) ();
                void (^m_onQueryCancelled) (WRLDSearchQuery *query);
                void (^m_onFocusEvent) ();
                void (^m_onSearchbarTextChanged) (NSString*);
                
                void AddEventListeners();
                void RemoveEventListeners();

                bool m_hasSearchResults;
                
                bool m_isNavigationHidden;
                
                CGFloat m_widgetAnimationOffset;

                TagCollection m_tagCollection;
                void UpdateDiscoverGroup(Menu::View::TSections& sections);
                void PopulateMenuData(Menu::View::TSections& sections);
                
            public:
                SearchWidgetView(WRLDSearchModel* searchModel,
                                 id<WRLDSearchProvider> searchProvider,
                                 id<WRLDSuggestionProvider> suggestionProvider,
                                 bool m_navigationEnabled,
                                 ExampleAppMessaging::TMessageBus& messageBus);
                ~SearchWidgetView();

                UIView* GetWidgetView() const;
                UIView* GetSpeechCaptureView() const;

                void OnSearchResultSelected(int index);

                void UpdateMenuSectionViews(Menu::View::TSections& sections);

                void SetFullyOnScreenOpen();
                void SetFullyOnScreenClosed();

                void PerformSearch(const std::string& query, const QueryContext& context);

                void ClearSearchResults();

                void InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                void RemoveResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback);
                
                void InsertSearchbarTextChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);
                void RemoveSearchbarTextChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback);
                
                void InsertOnNavigationRequestedCallback(Eegeo::Helpers::ICallback1<const int>& callback);
                void RemoveOnNavigationRequestedCallback(Eegeo::Helpers::ICallback1<const int>& callback);

                void HandleItemSelected(const std::string& menuText, int sectionIndex, int itemIndex);

                void InsertOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback);
                void RemoveOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback);

                void pushControlsOfScreenIfNeeded();
                void HandleViewOpenCompleted();
                void HandleViewCloseCompleted();

                void InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback);
                void RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback);

                void InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback);
                void RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback);

                void SetOnScreenStateToIntermediateValue(float value);
                void SetOnScreen();
                void SetOffScreen();

                void CloseMenu();

                void OnSearchResultsReceived();
                
                void NavigateTo(id<WRLDSearchResultModel> resultModel);

            private:
                void OnClearResults();

                void AddMenuSectionToGroup(WRLDMenuGroup* group,
                                           const Menu::View::IMenuSectionViewModel& section,
                                           int sectionIndex);

                WRLDMenuOption* AddMenuOption(WRLDMenuGroup* group,
                                              NSString* nsName,
                                              int sectionIndex);

                void AddMenuChildren(WRLDMenuOption* option,
                                     const Menu::View::IMenuSectionViewModel& section,
                                     int sectionIndex);
            };
        }
    }
}
