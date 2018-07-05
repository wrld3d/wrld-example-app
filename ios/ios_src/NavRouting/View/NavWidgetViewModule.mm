// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetViewModule.h"
#include "WrldNav/WrldNav.h"
#include "WrldNavWidget/WrldNavWidget.h"
#include "SearchResultPoiViewInterop.h"
#include "IOpenableControlViewModel.h"
#include "BidirectionalBus.h"
#include "NavWidgetView.h"
#include "NavWidgetSearchView.h"
#include "ISearchResultsRepository.h"
#include "NavWidgetLocationSetHandler.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            
            NavWidgetViewModule::NavWidgetViewModule(ExampleApp::OpenableControl::View::IOpenableControlViewModel& openable,
                                                     INavWidgetViewModel& viewModel,
                                                     WidgetSearchProvider* navSuggestionProvider,
                                                     SearchMenu::View::ISearchResultsRepository& suggestionsRespository,
                                                     ExampleAppMessaging::TMessageBus& messageBus_)
            {
                registerObserver("selectedDirectionIndex");
                
                m_pNavModel = [[WRLDNavModel alloc] init];
                
                setNavModel(m_pNavModel);
                
                m_pView = Eegeo_NEW(NavWidgetView)(m_pNavModel, getTopPanelVisibleHeightChangedCallbacks(), getBottomPanelVisibleHeightChangedCallbacks());
                
                m_pNavSearchView = Eegeo_NEW(NavWidgetSearchView)(navSuggestionProvider);
                
                m_pNavWidgetController = Eegeo_NEW(NavWidgetController)(*m_pView,
                                                                        viewModel,
                                                                        suggestionsRespository,
                                                                        messageBus_);
                
                m_pNavWidgetSearchController = [[NavWidgetSearchController alloc] initWithSearchView: m_pNavSearchView navWidgetView: m_pView];
                [m_pNavModel registerNavEventListener: m_pNavWidgetSearchController];
                
                m_pLocationSetHandler = Eegeo_NEW(NavWidgetLocationSetHandler)(m_pView, m_pNavWidgetSearchController);
            }
            
            NavWidgetViewModule::~NavWidgetViewModule()
            {
                Eegeo_DELETE m_pLocationSetHandler;
                
                [m_pNavModel unregisterNavEventListener: m_pNavWidgetSearchController];
                delete m_pNavWidgetController;
                delete m_pNavSearchView;
                delete m_pView;
            }
            
            UIView& NavWidgetViewModule::GetNavWidgetView() const
            {
                return *(m_pView->GetUIView());
            }
            
            UIView& NavWidgetViewModule::GetNavWidgetSearchView() const
            {
                return *(m_pNavSearchView->GetUIView());
            }
            
            NavWidgetController& NavWidgetViewModule::GetNavWidgetController() const
            {
                return *m_pNavWidgetController;
            }
            
            void NavWidgetViewModule::modelSet()
            {
                
            }
            
            void NavWidgetViewModule::changeReceived(const std::string& keyPath)
            {
                if(keyPath == "selectedDirectionIndex")
                {
                    m_pView->HandleSelectedDirectionIndexChangedCallback((int)m_pNavModel.selectedDirectionIndex);
                }
            }
            
            void NavWidgetViewModule::eventReceived(WRLDNavEvent key)
            {
                
                switch (key) {
                    case WRLDNavEventCloseSetupJourneyClicked:
                        m_pView->HandleClosedCallback();
                        break;
                    case WRLDNavEventSelectStartLocationClicked:
                        m_pView->HandleStartLocationClickedCallback();
                        break;
                    case WRLDNavEventSelectEndLocationClicked:
                        m_pView->HandleEndLocationClickedCallback();
                        break;
                    case WRLDNavEventStartLocationClearButtonClicked:
                        m_pView->HandleStartLocationClearButtonClickedCallback();
                        break;
                    case WRLDNavEventEndLocationClearButtonClicked:
                        m_pView->HandleEndLocationClearButtonCallback();
                        break;
                    case WRLDNavEventStartEndLocationsSwapped:
                        m_pView->HandleStartEndLocationsSwappedCallback();
                        break;
                    case WRLDNavEventStartEndButtonClicked:
                        m_pView->HandleStartEndRoutingButtonClickedCallback();
                        break;
                    default:
                        break;
                }
            }
            
            Eegeo::Helpers::CallbackCollection1<ExampleApp::NavRouting::View::INavWidgetView::THeight>& NavWidgetViewModule::getTopPanelVisibleHeightChangedCallbacks()
            {
                return m_topPanelVisibleHeightChangedCallbacks;
            }
            
            Eegeo::Helpers::CallbackCollection1<ExampleApp::NavRouting::View::INavWidgetView::THeight>& NavWidgetViewModule::getBottomPanelVisibleHeightChangedCallbacks()
            {
                return m_bottomPanelVisibleHeightChangedCallbacks;
            }
        }
    }
}
