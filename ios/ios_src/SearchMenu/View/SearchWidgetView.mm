// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchWidgetView.h"
#include "WidgetSearchResultTableViewCell.h"
#include "SearchWidgetMenuContext.h"
#include "WidgetQueryContext.h"
#include "MenuItemModel.h"
#include "ViewController.h"
#include "WidgetSearchResultTableViewCell.h"
#include "ISearchNavigationHandler.h"
#import <WrldSearchWidget/WRLDSearchQuery.h>

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetView::SearchWidgetView(WRLDSearchModel* searchModel,
                                               id<WRLDSearchProvider> searchProvider,
                                               id<WRLDSuggestionProvider> suggestionProvider,
                                               bool isNavigationEnabled,
                                               ExampleAppMessaging::TMessageBus& messageBus)
            : m_pSearchModel(searchModel)
            , m_tagCollection(messageBus)
            , m_hasSearchResults(false)
            , m_hasPopulatedData(false)
            , m_isNavigationHidden(!isNavigationEnabled)
            {
                m_pMenuModel = [[WRLDSearchMenuModel alloc] init];
                m_pSearchProviderHandle = [m_pSearchModel addSearchProvider: searchProvider];
                m_pSuggestionProviderHandle = [m_pSearchModel addSuggestionProvider: suggestionProvider];

                m_pSearchWidgetView = [[[WRLDSearchWidgetView alloc] init] autorelease];
                [m_pSearchWidgetView useSearchModel:m_pSearchModel];
                [m_pSearchWidgetView useMenuModel:m_pMenuModel];

                [m_pSearchWidgetView displaySearchProvider: m_pSearchProviderHandle];
                [m_pSearchWidgetView displaySuggestionProvider: m_pSuggestionProviderHandle];

                UIViewController *rootViewController = [UIApplication sharedApplication].delegate.window.rootViewController;
                UIEdgeInsets safeInsets = [rootViewController safeInsets];
                
                CGRect screenRect = rootViewController.view.bounds;
                
                CGFloat screenWidth = screenRect.size.width;
                CGFloat iphoneMargin = 20;
                CGFloat iPadMargin = 20;
                CGFloat iPhoneWidgetWidth = screenWidth - 2*iphoneMargin;
                CGFloat iPadWidgetWidth = 375;
                
                CGFloat heightIphone = screenRect.size.height - 2*iphoneMargin - safeInsets.bottom;
                CGFloat heightIpad = screenRect.size.height - 2*iPadMargin - safeInsets.bottom;

                CGRect iPadFrame = CGRectMake(iPadMargin, safeInsets.top,  iPadWidgetWidth , heightIpad) ;
                CGRect iPhoneFrame = CGRectMake(iphoneMargin, safeInsets.top, iPhoneWidgetWidth , heightIphone);
            
                CGRect searchFrame = ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad) ? iPadFrame : iPhoneFrame;
                
                CGFloat searchBoxHeight = 50;
                m_widgetAnimationOffset = - searchFrame.origin.y - searchBoxHeight;

                m_pSearchWidgetView.frame = searchFrame;

                CGAffineTransform transform = CGAffineTransformMakeTranslation(0.0,m_widgetAnimationOffset);
                m_pSearchWidgetView.transform = transform;

                NSBundle* resourceBundle = [NSBundle bundleForClass:[WidgetSearchResultTableViewCell class]];
                UINib* nib = [UINib nibWithNibName: @"WidgetSearchResultTableViewCell" bundle:resourceBundle];

                [m_pSearchWidgetView registerNib:nib forUseWithResultsTableCellIdentifier:@"WidgetSearchResultTableViewCell"];

                m_pMenuGroups = [[NSMutableDictionary alloc] init];
                m_pMenuOptions = [[NSMutableDictionary alloc] init];
                
                m_pSpeechCapture = [[WRLDSpeechCapture alloc] initWithFrame: [UIScreen mainScreen].bounds];
                [m_pSearchWidgetView enableVoiceSearch:m_pSpeechCapture];
                
                AddEventListeners();
            }
            
            
            SearchWidgetView::~SearchWidgetView()
            {
                RemoveEventListeners();
                
                [m_pSearchWidgetView disableVoiceSearch];
                
                [m_pSpeechCapture release];
                [m_pMenuOptions release];
                [m_pMenuGroups release];
                [m_pMenuModel release];
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
                    [m_pSearchWidgetView resignFocus];
                    
                    WidgetSearchResultModel* selectedResultModelWithIndex = (WidgetSearchResultModel*) selectedResultModel;
                    if (selectedResultModelWithIndex != nil)
                    {
                        this->OnSearchResultSelected((int)selectedResultModelWithIndex.index);
                    }
                    
                };
                                
                m_willPopulateResultCell = ^(WRLDSearchResultTableViewCell *cell)
                {
                    if([cell isKindOfClass:[WidgetSearchResultTableViewCell class]])
                    {
                        WidgetSearchResultTableViewCell* castCell = (WidgetSearchResultTableViewCell*) cell;
                        [castCell setNavigationHidden: m_isNavigationHidden];
                        if(!m_isNavigationHidden){
                            [castCell assignNavigationHandler: this];
                        }
                    }
                };
                
                [m_pSearchWidgetView.searchResultContentObserver addWillPopulateEvent: m_willPopulateResultCell];
                
                [m_pSearchWidgetView.searchSelectionObserver addResultSelectedEvent:m_onResultSelection];
                
                m_onFocusEvent = ^{
                    this->pushControlsOfScreenIfNeeded();
                };
                
                [m_pSearchWidgetView.observer addSearchWidgetGainedFocusEvent:m_onFocusEvent];
                [m_pSearchWidgetView.observer addSearchWidgetResignedFocusEvent:m_onFocusEvent];
                
                m_onMenuSelection = ^(NSObject* selectedOptionContext)
                {
                    SearchWidgetMenuContext* widgetMenuContext = (SearchWidgetMenuContext*) selectedOptionContext;
                    if (widgetMenuContext != nil)
                    {
                        const std::string menuText = [widgetMenuContext.menuText cStringUsingEncoding: NSUTF8StringEncoding];
                        int sectionIndex = (int) widgetMenuContext.sectionIndex;
                        int itemIndex = (int) widgetMenuContext.itemIndex;
                        
                        this->HandleItemSelected(menuText, sectionIndex, itemIndex);
                        
                        [m_pSearchWidgetView closeMenu];
                        if (m_tagCollection.HasTag(menuText))
                        {
                            [m_pSearchWidgetView showResultsView];
                        }
                    }
                };
                
                [m_pSearchWidgetView.menuObserver addOptionSelectedEvent:m_onMenuSelection];
                
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
                
                [m_pSearchWidgetView.observer addSearchResultsClearedEvent:m_onResultsCleared];
                [m_pSearchWidgetView.observer addSearchResultsReceivedEvent:m_onResultsReceived];

                [m_pSearchModel.searchObserver addQueryCancelledEvent:m_onQueryCancelled];
                
                m_onSearchbarTextChanged = ^(NSString* newText)
                {
                    std::string stlString = std::string([newText UTF8String]);
                    m_searchbarTextChangedCallbacks.ExecuteCallbacks(stlString);
                };
                
                [m_pSearchWidgetView.observer addSearchbarTextChangedEvent:m_onSearchbarTextChanged];
                
            }
            
            void SearchWidgetView::RemoveEventListeners(){
                [m_pSearchWidgetView.observer removeSearchbarTextChangedEvent:m_onSearchbarTextChanged];
                
                [m_pSearchModel.searchObserver removeQueryCancelledEvent:m_onQueryCancelled];

                [m_pSearchWidgetView.observer removeSearchResultsReceivedEvent:m_onResultsReceived];
                [m_pSearchWidgetView.observer removeSearchResultsClearedEvent:m_onResultsCleared];

                [m_pSearchWidgetView.menuObserver removeOptionSelectedEvent:m_onMenuSelection];
                
                [m_pSearchWidgetView.searchResultContentObserver removeWillPopulateEvent: m_willPopulateResultCell];

                [m_pSearchWidgetView.observer removeSearchWidgetGainedFocusEvent :m_onFocusEvent];
                [m_pSearchWidgetView.observer removeSearchWidgetResignedFocusEvent:m_onFocusEvent];

                [m_pSearchWidgetView.searchSelectionObserver removeResultSelectedEvent:m_onResultSelection];
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

            UIView* SearchWidgetView::GetWidgetView() const
            {
                return (UIView*)m_pSearchWidgetView;
            }
            
            UIView* SearchWidgetView::GetSpeechCaptureView() const
            {
                return (UIView*)m_pSpeechCapture;
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
                
                const size_t numSections = sections.size();
                
                for (int sectionIndex = 0; sectionIndex < numSections; sectionIndex++)
                {
                    Menu::View::IMenuSectionViewModel& section = *sections[sectionIndex];
                    
                    NSString* nsName = [NSString stringWithUTF8String:section.Name().c_str()];
                    
                    WRLDMenuOption* option = m_pMenuOptions[nsName];
                    [option removeAllChildren];
                    
                    if (section.IsExpandable())
                    {
                        AddMenuChildren(option, section, sectionIndex);
                    }
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
                        
                       [m_pMenuGroups setObject:group forKey:nsName];
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
                widgetQueryContext.usesLocation = (BOOL) context.UsesLocation();
                widgetQueryContext.usesRadius = (BOOL) context.UsesRadius();

                widgetQueryContext.tagText = [NSString stringWithUTF8String:context.TagText().c_str()];

                widgetQueryContext.latitude = (CGFloat) context.Location().GetLatitude();
                widgetQueryContext.longtitude = (CGFloat) context.Location().GetLongitude();
                widgetQueryContext.altitude = (CGFloat) context.Location().GetAltitude();
                widgetQueryContext.radius = (CGFloat) context.Radius();

                [m_pSearchModel getSearchResultsForString:queryString
                                              withOptions:[WRLDSearchQueryOptions withContext:widgetQueryContext]];
            }

            void SearchWidgetView::ClearSearchResults()
            {
                // add here when/if the widget API allows it, if needed
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
            
            void SearchWidgetView::InsertSearchbarTextChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                m_searchbarTextChangedCallbacks.AddCallback(callback);
            }
            
            void SearchWidgetView::RemoveSearchbarTextChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                m_searchbarTextChangedCallbacks.RemoveCallback(callback);
            }
            
            void SearchWidgetView::InsertOnNavigationRequestedCallback(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_navigationRequestedCallbacks.AddCallback(callback);
            }
            
            void SearchWidgetView::RemoveOnNavigationRequestedCallback(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_navigationRequestedCallbacks.RemoveCallback(callback);
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
              
                bool shouldTakeFocus = m_pSearchWidgetView.hasFocus;
                
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
                [m_pSearchWidgetView hideResultsView];
                [m_pSearchWidgetView closeMenu];
               
                CGAffineTransform transform = CGAffineTransformMakeTranslation(0.0,m_widgetAnimationOffset*value);

                [UIView animateWithDuration:0.3 animations:^{
                    m_pSearchWidgetView.transform = transform;
                }];
            }

            void SearchWidgetView::SetOnScreen()
            {
                [UIView animateWithDuration:0.3 animations:^{
                    m_pSearchWidgetView.transform = CGAffineTransformIdentity;
                }];
            }

            void SearchWidgetView::SetOffScreen()
            {
                [m_pSearchWidgetView hideResultsView];
                [m_pSearchWidgetView closeMenu];

                CGAffineTransform transform = CGAffineTransformMakeTranslation(0.0,m_widgetAnimationOffset);

                [UIView animateWithDuration:0.3 animations:^{
                    m_pSearchWidgetView.transform = transform;
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
                [m_pMenuOptions setObject:menuOption forKey:nsName];

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
                [m_pSearchWidgetView hideResultsView];
                [m_pSearchWidgetView closeMenu];
            }
            
            void SearchWidgetView::NavigateTo(id<WRLDSearchResultModel> resultModel)
            {
                WidgetSearchResultModel* selectedResultModelWithIndex = (WidgetSearchResultModel*) resultModel;
                if (selectedResultModelWithIndex != nil)
                {
                    int index = (int)selectedResultModelWithIndex.index;
                    m_navigationRequestedCallbacks.ExecuteCallbacks(index);
                }
            }
        }
    }
}
