// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchWidgetView.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetView::SearchWidgetView(SearchMenuView* view):
            m_pView(view)
            {
                
                WRLDSearchMenuModel* menuModel = [[WRLDSearchMenuModel alloc] init];
                WRLDSearchModel* searchModel = [[WRLDSearchModel alloc] init];
                
                m_pSearchWidgetViewController = [[WRLDSearchWidgetViewController alloc] initWithSearchModel:searchModel menuModel:menuModel];
                
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
            
            void SearchWidgetView::UpdateMenuSectionViews(Menu::View::TSections& sections, bool contentsChanged)
            {
            }
            
            void SearchWidgetView::HandleItemSelected(int sectionIndex, int itemIndex)
            {
            }
            
            void SearchWidgetView::InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
            }
            
            void SearchWidgetView::RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
            }
            
            void SearchWidgetView::RefreshSearch(const std::string& query, const QueryContext& context)
            {
            }
            
            void SearchWidgetView::InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
            }
            
            void SearchWidgetView::RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
            }
            
            void SearchWidgetView::InsertResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
            }
            
            void SearchWidgetView::RemoveResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
            }
        }
    }
}
