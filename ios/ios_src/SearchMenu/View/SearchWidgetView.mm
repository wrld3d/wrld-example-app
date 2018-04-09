// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchWidgetView.h"
#include "WidgetSearchResultTableViewCell.h"
#include "SearchWidgetMenuContext.h"
#include "WidgetQueryContext.h"
#include "MenuItemModel.h"
#include "ViewController.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetView::SearchWidgetView(id<WRLDSearchProvider> searchProvider,
                                               id<WRLDSuggestionProvider> suggestionProvider,
                                               ExampleAppMessaging::TMessageBus& messageBus)
            : m_tagCollection(messageBus)
            , m_hasSearchResults(false)
            , m_hasPopulatedData(false)
            {
                m_pSearchModel = [[WRLDSearchModel alloc] init];
                m_pMenuModel = [[WRLDSearchMenuModel alloc] init];
                m_pSearchProviderHandle = [m_pSearchModel addSearchProvider: searchProvider];
                m_pSuggestionProviderHandle = [m_pSearchModel addSuggestionProvider: suggestionProvider];

                m_pSearchWidgetViewController = [[WRLDSearchWidgetViewController alloc] initWithSearchModel:m_pSearchModel menuModel: m_pMenuModel];

                [m_pSearchWidgetViewController displaySearchProvider: m_pSearchProviderHandle];
                [m_pSearchWidgetViewController displaySuggestionProvider: m_pSuggestionProviderHandle];

                UIWindow *window = [[UIApplication sharedApplication] keyWindow];
                ViewController *rootViewController = (ViewController *)window.rootViewController;
                UIEdgeInsets safeInsets = [rootViewController safeInsets];
                
                CGRect screenRect = rootViewController.view.bounds;
                
                CGFloat screenWidth = screenRect.size.width;
                CGFloat iphoneMargin = 20;
                CGFloat iPadMargin = 20;
                CGFloat iPhoneWidgetWidth = screenWidth - 2*iphoneMargin;
                CGFloat iPadWidgetWidth = 375;
                
                CGFloat heightIphone = screenRect.size.height - 2*iphoneMargin;
                CGFloat heightIpad = screenRect.size.height - 2*iPadMargin;

                CGRect iPadFrame = CGRectMake(iPadMargin, safeInsets.top,  iPadWidgetWidth , heightIpad) ;
                CGRect iPhoneFrame = CGRectMake(iphoneMargin, safeInsets.top, iPhoneWidgetWidth , heightIphone);
            
                CGRect searchFrame = ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad) ? iPadFrame : iPhoneFrame;
                
                CGFloat searchBoxHeight = 50;
                m_widgetAnimationOffset = - searchFrame.origin.y - searchBoxHeight;
                
                UIView *widget = m_pSearchWidgetViewController.view;

                widget.frame = searchFrame;

                CGAffineTransform transform = CGAffineTransformMakeTranslation(0.0,m_widgetAnimationOffset);
                widget.transform = transform;

                NSBundle* resourceBundle = [NSBundle bundleForClass:[WidgetSearchResultTableViewCell class]];
                UINib* nib = [UINib nibWithNibName: @"WidgetSearchResultTableViewCell" bundle:resourceBundle];

                [m_pSearchWidgetViewController registerNib:nib forUseWithResultsTableCellIdentifier:@"WidgetSearchResultTableViewCell"];

                m_menuGroups = [[NSMutableDictionary alloc] init];
                m_menuOptions = [[NSMutableDictionary alloc] init];
                
                [m_pSearchWidgetViewController setSearchBarPlaceholder:@"Search Bloomberg"];
                
                m_pSpeechHandler = [[WRLDSpeechHandler alloc] initWithFrame: [UIScreen mainScreen].bounds];
                [m_pSpeechHandler setPrompt:@"Search Bloomberg"];
                [m_pSearchWidgetViewController enableVoiceSearch:m_pSpeechHandler];
                
                AddEventListeners();
            }
            
            
            SearchWidgetView::~SearchWidgetView()
            {
                RemoveEventListeners();
                
                [m_pSearchWidgetViewController disableVoiceSearch];
                
                [m_pSpeechHandler release];
                [m_menuOptions release];
                [m_menuGroups release];
                [m_pMenuModel release];
                [m_pSearchModel release];

            }
            
            void SearchWidgetView::AddEventListeners(){
                
                m_onResultSelection = ^(id<WRLDSearchResultModel> selectedResultModel)
                {
                    /*
                     MB NOTE: If a UIView is currently firstResponder, then disabling userInteraction on the
                         view Hierarchy (which selecting a result does via starting a transition) will cause the
                         previous firstResponder to reassume control when userInteraction is enabled (as the transition ends).  To prevent this, the firstResponder must resign control BEFORE
                         we disable userInteraction.
                     */
                    [m_pSearchWidgetViewController resignFocus];
                    
                    WidgetSearchResultModel* selectedResultModelWithIndex = (WidgetSearchResultModel*) selectedResultModel;
                    if (selectedResultModelWithIndex != nil)
                    {
                        this->OnSearchResultSelected((int)selectedResultModelWithIndex.index);
                    }
                    
                };
                
                [m_pSearchWidgetViewController.searchSelectionObserver addResultSelectedEvent:m_onResultSelection];
                
                m_onFocusEvent = ^{
                    this->pushControlsOfScreenIfNeeded();
                };
                
                [m_pSearchWidgetViewController.observer addSearchbarResignedFocusEvent:m_onFocusEvent];
                [m_pSearchWidgetViewController.observer addSearchbarGainedFocusEvent:m_onFocusEvent];
               
                
                m_onMenuEvent = ^(BOOL opened){
                    this->pushControlsOfScreenIfNeeded();
                };
                
                m_onMenuSelection = ^(NSObject* selectedOptionContext)
                {
                    SearchWidgetMenuContext* widgetMenuContext = (SearchWidgetMenuContext*) selectedOptionContext;
                    if (widgetMenuContext != nil)
                    {
                        const std::string menuText = [widgetMenuContext.menuText cStringUsingEncoding: NSUTF8StringEncoding];
                        int sectionIndex = (int) widgetMenuContext.sectionIndex;
                        int itemIndex = (int) widgetMenuContext.itemIndex;
                        
                        this->HandleItemSelected(menuText, sectionIndex, itemIndex);
                        
                        if (m_tagCollection.HasTag(menuText))
                        {
                            [m_pSearchWidgetViewController closeMenu];
                            [m_pSearchWidgetViewController showResultsView];
                        }
                    }
                };

                
                [m_pSearchWidgetViewController.menuObserver addOptionSelectedEvent:m_onMenuSelection];
               
                [m_pSearchWidgetViewController.menuObserver addOpenedEvent:m_onMenuEvent];
                [m_pSearchWidgetViewController.menuObserver addClosedEvent:m_onMenuEvent];
                
                m_onQueryEvent =^(WRLDSearchQuery *query){
                    this->pushControlsOfScreenIfNeeded();
                };
                
                m_onResultsCleared = ^()
                {
                    OnClearResults();
                };
                m_onQueryCancelled = ^(WRLDSearchQuery *query)
                {
                    OnClearResults();
                };
                
                m_onResultsReceived = ^()
                {
                    OnSearchResultsReceived();
                };
                
                [m_pSearchWidgetViewController.observer addSearchResultsClearedEvent:m_onResultsCleared];
                [m_pSearchWidgetViewController.observer addSearchResultsReceivedEvent:m_onResultsReceived];

                [m_pSearchModel.searchObserver addQueryStartingEvent:m_onQueryEvent];
                [m_pSearchModel.searchObserver addQueryCompletedEvent:m_onQueryEvent];
                [m_pSearchModel.searchObserver addQueryCancelledEvent:m_onQueryEvent];
                [m_pSearchModel.searchObserver addQueryCancelledEvent:m_onQueryCancelled];
                
            }
            
            void SearchWidgetView::RemoveEventListeners(){
                [m_pSearchModel.searchObserver removeQueryCancelledEvent:m_onQueryCancelled];
                [m_pSearchModel.searchObserver removeQueryCancelledEvent:m_onQueryEvent];
                [m_pSearchModel.searchObserver removeQueryCompletedEvent:m_onQueryEvent];
                [m_pSearchModel.searchObserver removeQueryStartingEvent:m_onQueryEvent];

                [m_pSearchWidgetViewController.observer removeSearchResultsReceivedEvent:m_onResultsReceived];
                [m_pSearchWidgetViewController.observer removeSearchResultsClearedEvent:m_onResultsCleared];

                [m_pSearchWidgetViewController.menuObserver removeClosedEvent:m_onMenuEvent];
                [m_pSearchWidgetViewController.menuObserver removeOpenedEvent:m_onMenuEvent];
                [m_pSearchWidgetViewController.menuObserver removeOptionSelectedEvent:m_onMenuSelection];

                [m_pSearchWidgetViewController.observer removeSearchbarGainedFocusEvent:m_onFocusEvent];
                [m_pSearchWidgetViewController.observer removeSearchbarResignedFocusEvent:m_onFocusEvent];

                [m_pSearchWidgetViewController.searchSelectionObserver removeResultSelectedEvent:m_onResultSelection];
            }
            
            void SearchWidgetView::OnSearchResultsReceived()
            {
                m_hasSearchResults = true;
            }
            
            void SearchWidgetView::OnClearResults()
            {
                m_searchClearedCallbacks.ExecuteCallbacks();
                m_hasSearchResults = false;
            }

            UIViewController* SearchWidgetView::GetWidgetController() const
            {
                return (UIViewController*)m_pSearchWidgetViewController;
            }

            UIView* SearchWidgetView::GetWidgetView() const
            {
                return (UIView*)m_pSearchWidgetViewController.view;
            }
            
            UIView* SearchWidgetView::GetSpeechHandlerView() const
            {
                return (UIView*)m_pSpeechHandler;
            }

            void SearchWidgetView::OnSearchResultSelected(int index)
            {
                m_resultSelectedCallbacks.ExecuteCallbacks(index);
            }

            void SearchWidgetView::UpdateMenuSectionViews(Menu::View::TSections& sections)
            {
                if(m_hasPopulatedData != true){
                    PopulateMenuData(sections);
                    m_hasPopulatedData = true;
                    return;
                }
                UpdateDiscoverGroup(sections);
                
                const size_t numSections = sections.size();
                
                for (int sectionIndex = 0; sectionIndex < numSections; sectionIndex++)
                {
                    Menu::View::IMenuSectionViewModel& section = *sections[sectionIndex];
                    
                    NSString* nsName = [NSString stringWithUTF8String:section.Name().c_str()];
                    
                    WRLDMenuOption* option = m_menuOptions[nsName];
                    [option removeAllChildren];
                    
                    if (section.IsExpandable())
                    {
                        AddMenuChildren(option, section, sectionIndex);
                    }
                }
            }
            
            void SearchWidgetView::UpdateDiscoverGroup(Menu::View::TSections& sections){
                NSString *groupName = @"Discover";
                WRLDMenuGroup *group = m_menuGroups[groupName];
                
                BOOL shouldShowDiscover = false;
                
                const size_t numSections = sections.size();
                
                for (int sectionIndex = 0; sectionIndex < numSections; sectionIndex++)
                {
                    if (sectionIndex == 0 || sections[sectionIndex]->IsGroupStart())
                    {
                        Menu::View::IMenuSectionViewModel& section = *sections[sectionIndex];
                        NSString* optionName = [NSString stringWithUTF8String:section.Name().c_str()];
                        if([optionName isEqualToString:groupName]){
                            WRLDMenuOption *option = m_menuOptions[optionName];
                            //TODO: when widget is updated so that it's possible, check if group has options rather than removing option.
                            [group removeOption:option];
                            [group addOption:option];
                            shouldShowDiscover = true;
                        }
                    }
                }
                
                if(shouldShowDiscover != true){
                    [group removeAllOptions];
                }
                
            }
            
            void SearchWidgetView::PopulateMenuData(Menu::View::TSections& sections){
                const size_t numSections = sections.size();
                
                WRLDMenuGroup* group = NULL;
                
                for (int sectionIndex = 0; sectionIndex < numSections; sectionIndex++)
                {
                    if (sectionIndex == 0 || sections[sectionIndex]->IsGroupStart())
                    {
                        group = [[WRLDMenuGroup alloc] init];
                        
                        [m_pMenuModel addMenuGroup:group];
                        
                        Menu::View::IMenuSectionViewModel& section = *sections[sectionIndex];
                       NSString* nsName = [NSString stringWithUTF8String:section.Name().c_str()];
                        
                       [m_menuGroups setObject:group forKey:nsName];
                    }
                    
                    AddMenuSectionToGroup(group, *sections[sectionIndex], sectionIndex);
                }
            }
            
            void SearchWidgetView::PerformSearch(const std::string& query, const QueryContext& context)
            {
                NSString* queryString = [NSString stringWithUTF8String:query.c_str()];

                WidgetQueryContext* widgetQueryContext = [[WidgetQueryContext alloc] init];

                widgetQueryContext.clearPreviousResults = (BOOL) context.ClearPreviousResults();
                widgetQueryContext.isTag = (BOOL) context.IsTag();
                widgetQueryContext.shouldTryInterior = (BOOL) context.ShouldTryInterior();
                widgetQueryContext.shouldZoomToBuildingsView = (BOOL) context.ShouldZoomToBuildingsView();
                widgetQueryContext.usesLocation = (BOOL) context.UsesLocation();
                widgetQueryContext.usesRadius = (BOOL) context.UsesRadius();

                widgetQueryContext.tagText = [NSString stringWithUTF8String:context.TagText().c_str()];

                widgetQueryContext.latitude = (CGFloat) context.Location().GetLatitude();
                widgetQueryContext.longtitude = (CGFloat) context.Location().GetLongitude();
                widgetQueryContext.altitude = (CGFloat) context.Location().GetAltitude();
                widgetQueryContext.radius = (CGFloat) context.Radius();

                [m_pSearchModel getSearchResultsForString:queryString withContext:widgetQueryContext];
            }

            void SearchWidgetView::AddMenuSectionToGroup(WRLDMenuGroup* group,
                                                         const Menu::View::IMenuSectionViewModel& section,
                                                         int sectionIndex)
            {
                NSString* nsName = [NSString stringWithUTF8String:section.Name().c_str()];

                WRLDMenuOption* option = AddMenuOption(group, nsName, sectionIndex);
                if (section.IsExpandable())
                {
                    AddMenuChildren(option, section, sectionIndex);
                }
            }

            void SearchWidgetView::InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::InsertResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_resultSelectedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_resultSelectedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::HandleItemSelected(const std::string& menuText, int sectionIndex, int itemIndex)
            {
                m_onItemSelectedCallbacks.ExecuteCallbacks(menuText, sectionIndex, itemIndex);
            }

            void SearchWidgetView::InsertOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback)
            {
                m_onItemSelectedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback)
            {
                m_onItemSelectedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::pushControlsOfScreenIfNeeded(){
              
                // TODO: Add search results visibility observer event, Has search results event.
                bool hasVisibleSearchResults = m_pSearchWidgetViewController.isResultsViewVisible && (m_hasSearchResults || m_pSearchModel.isSearchQueryInFlight);

              
                bool shouldTakeFocus = m_pSearchWidgetViewController.searchbarHasFocus || hasVisibleSearchResults || m_pSearchWidgetViewController.isMenuOpen;
                
                if( shouldTakeFocus )
                {
                    HandleViewOpenCompleted();
                }
                else
                {
                    HandleViewCloseCompleted();
                }
            }

            void SearchWidgetView::HandleViewOpenCompleted()
            {
                m_onViewOpenedCallbacks.ExecuteCallbacks();
            }

            void SearchWidgetView::HandleViewCloseCompleted()
            {
                m_onViewClosedCallbacks.ExecuteCallbacks();
            }

            void SearchWidgetView::InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewOpenedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewOpenedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewClosedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_onViewClosedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::SetOnScreenStateToIntermediateValue(float value)
            {
                [m_pSearchWidgetViewController hideResultsView];
                [m_pSearchWidgetViewController closeMenu];
                UIView *widget = (UIView*)m_pSearchWidgetViewController.view;
               
                CGAffineTransform transform = CGAffineTransformMakeTranslation(0.0,m_widgetAnimationOffset*value);

                [UIView animateWithDuration:0.3 animations:^{
                    widget.transform = transform;
                }];
            }

            void SearchWidgetView::SetFullyOnScreen()
            {
                UIView *widget = (UIView*)m_pSearchWidgetViewController.view;
                
                [UIView animateWithDuration:0.3 animations:^{
                    widget.transform = CGAffineTransformIdentity;
                }];
            }

            void SearchWidgetView::SetFullyOffScreen()
            {
                [m_pSearchWidgetViewController hideResultsView];
                [m_pSearchWidgetViewController closeMenu];
                UIView *widget = (UIView*)m_pSearchWidgetViewController.view;
                
                CGAffineTransform transform = CGAffineTransformMakeTranslation(0.0,m_widgetAnimationOffset);

                [UIView animateWithDuration:0.3 animations:^{
                    widget.transform = transform;
                }];
            }

            WRLDMenuOption* SearchWidgetView::AddMenuOption(WRLDMenuGroup* group,
                                                            NSString* nsName,
                                                            int sectionIndex)
            {
                SearchWidgetMenuContext* widgetMenuContext = [[SearchWidgetMenuContext alloc] init];

                widgetMenuContext.menuText = nsName;
                widgetMenuContext.sectionIndex = (NSInteger) sectionIndex;
                widgetMenuContext.itemIndex = 0;

                WRLDMenuOption* menuOption = [[WRLDMenuOption alloc] initWithText:nsName
                                                                          context:widgetMenuContext];

                [group addOption:menuOption];
                [m_menuOptions setObject:menuOption forKey:nsName];

                return menuOption;
            }

            void SearchWidgetView::AddMenuChildren(WRLDMenuOption* option,
                                                   const Menu::View::IMenuSectionViewModel& section,
                                                   int sectionIndex)
            {
                for (int childIndex = 0; childIndex < section.GetTotalItemCount(); childIndex++)
                {
                    const Menu::View::MenuItemModel& sectionChild = section.GetItemAtIndex(childIndex);

                    NSString* nsChildName = [NSString stringWithUTF8String:sectionChild.Name().c_str()];

                    std::string fullIconName = "icon1_" + sectionChild.Icon();
                    NSString* nsChildIcon = [NSString stringWithUTF8String:fullIconName.c_str()];

                    SearchWidgetMenuContext* widgetMenuParentContext = (SearchWidgetMenuContext*) option.context;
                    if (widgetMenuParentContext != nil)
                    {
                        SearchWidgetMenuContext* widgetMenuChildContex = [[SearchWidgetMenuContext alloc] init];

                        widgetMenuChildContex.menuText = nsChildName;
                        widgetMenuChildContex.sectionIndex = widgetMenuParentContext.sectionIndex;
                        widgetMenuChildContex.itemIndex = (NSInteger) childIndex;

                        WRLDMenuChild* child = [[WRLDMenuChild alloc] initWithText:nsChildName
                                                                              icon:nsChildIcon
                                                                           context:widgetMenuChildContex];
                        [option addChild:child];
                    }
                }
            }

            void SearchWidgetView::CloseMenu()
            {
                [m_pSearchWidgetViewController hideResultsView];
                [m_pSearchWidgetViewController closeMenu];
            }
        }
    }
}
