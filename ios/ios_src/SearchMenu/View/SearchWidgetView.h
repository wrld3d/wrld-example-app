// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchWidgetView.h"
#include "WidgetSearchResultModel.h"
#include "TagCollection.h"

#import <WrldSearchWidget/WrldSearchWidget.h>

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchWidgetView : public SearchMenu::View::ISearchWidgetView
            {
            private:
                WRLDSearchWidgetViewController* m_pSearchWidgetViewController;
                WRLDSearchModel* m_pSearchModel;
                WRLDSearchMenuModel* m_pMenuModel;
                WRLDSearchProviderHandle* m_pSearchProviderHandle;
                WRLDSuggestionProviderHandle* m_pSuggestionProviderHandle;
                WRLDSpeechHandler* m_pSpeechHandler;

                Eegeo::Helpers::CallbackCollection0 m_searchClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<int> m_resultSelectedCallbacks;
                Eegeo::Helpers::CallbackCollection3<const std::string&, int, int> m_onItemSelectedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewOpenedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_onViewClosedCallbacks;
                
                NSMutableDictionary *m_menuGroups;
                NSMutableDictionary *m_menuOptions;
                
                bool m_hasPopulatedData;
                
                void (^m_onResultSelection) (id<WRLDSearchResultModel>);
                void (^m_onMenuSelection) (NSObject*);
                void (^m_onResultsReceived) ();
                void (^m_onResultsCleared) ();
                void (^m_onQueryCancelled) (WRLDSearchQuery *query);
                void (^m_onFocusEvent) ();
                
                void AddEventListeners();
                void RemoveEventListeners();

                bool m_hasSearchResults;
                
                CGFloat m_widgetAnimationOffset;

                TagCollection m_tagCollection;
                void UpdateDiscoverGroup(Menu::View::TSections& sections);
                void PopulateMenuData(Menu::View::TSections& sections);
            public:
                SearchWidgetView(id<WRLDSearchProvider> searchProvider,
                                 id<WRLDSuggestionProvider> suggestionProvider,
                                 ExampleAppMessaging::TMessageBus& messageBus);
                ~SearchWidgetView();

                UIViewController* GetWidgetController() const;
                UIView* GetWidgetView() const;
                UIView* GetSpeechHandlerView() const;

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
                void SetFullyOnScreen();
                void SetFullyOffScreen();

                void CloseMenu();

                void OnSearchResultsReceived();

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
