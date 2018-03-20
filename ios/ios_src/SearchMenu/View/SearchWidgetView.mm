// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchWidgetView.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetView::SearchWidgetView(SearchMenuView* view,
                                               id<WRLDSearchProvider> searchProvider,
                                               id<WRLDSuggestionProvider> suggestionProvider):
            m_pView(view)
            {
                m_pSearchModel = [[WRLDSearchModel alloc] init];
                m_pSearchProviderHandle = [m_pSearchModel addSearchProvider: searchProvider];
                m_pSuggestionProviderHandle = [m_pSearchModel addSuggestionProvider: suggestionProvider];
                
                WRLDSearchMenuModel* menuModel = [[WRLDSearchMenuModel alloc] init];
                
                m_pSearchWidgetViewController = [[WRLDSearchWidgetViewController alloc] initWithSearchModel:m_pSearchModel menuModel:menuModel];
                
                [m_pSearchWidgetViewController displaySearchProvider: m_pSearchProviderHandle];
                [m_pSearchWidgetViewController displaySuggestionProvider: m_pSuggestionProviderHandle];
                
                void (^onResultSelection) (id<WRLDSearchResultModel>) = ^(id<WRLDSearchResultModel> selectedResultModel)
                {
                    WidgetSearchResultModel* selectedResultModelWithIndex = (WidgetSearchResultModel*) selectedResultModel;
                    if (selectedResultModelWithIndex != nil)
                    {
                        this->OnSearchResultSelected(selectedResultModelWithIndex.index);
                    }
                };
                
                [[m_pSearchWidgetViewController searchSelectionObserver] addResultSelectedEvent:onResultSelection];
                
                CGRect searchFrame = ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad) ?
                CGRectMake(20, 20, 375, CGRectGetHeight(m_pView.bounds) - 40) :   // ipad
                CGRectMake(10, 10, CGRectGetWidth(m_pView.bounds) - 20, CGRectGetHeight(m_pView.bounds) - 20); // iphone
                
                m_pSearchWidgetViewController.view.frame = searchFrame;
            }
            
            SearchWidgetView::~SearchWidgetView()
            {
            }
            
            UIViewController* SearchWidgetView::GetWidgetController() const
            {
                return (UIViewController*)m_pSearchWidgetViewController;
            }
            
            UIView* SearchWidgetView::GetWidgetView() const
            {
                return (UIView*)m_pSearchWidgetViewController.view;
            }
            
            void SearchWidgetView::OnSearchResultSelected(int index)
            {
                m_resultSelectedCallbacks.ExecuteCallbacks(index);
            }
            
            void SearchWidgetView::UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged)
            {
            }
            
            void SearchWidgetView::PerformSearch(const std::string& query, const QueryContext& context)
            {
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
        }
    }
}
