
// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PathDrawingController.h"
#include "RouteBuilder.h"
#include "RouteStyle.h"
#include "WayPointsRepository.h"
#include "WayPointType.h"
#include "LatLongAltitude.h"
#include "IMenuSectionViewModel.h"
#include "IMenuModel.h"
#include "DirectionRouteGeometryModel.h"
#include "SearchResultItemModel.h"


using namespace Eegeo;
using namespace Eegeo::Routes;

namespace ExampleApp
{
    namespace PathDrawing
    {
        

        PathDrawingController::PathDrawingController(Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                                     Eegeo::Routes::RouteService& routeService

                                                     , AppCamera::SdkModel::AppGlobeCameraWrapper& cameraWrapper
                                                     , PathDrawing::SdkModel::IWayPointsRepository& wayPointsRepository
                                                     , ExampleAppMessaging::TMessageBus& messageBus)
        : m_routeService(routeService)
        , m_cameraWrapper(cameraWrapper)
        , m_pWayPointsRepository(wayPointsRepository)
        , m_createdRoutes(false)
        , m_messageBus(messageBus)
        , m_searchSectionViewModel(searchSectionViewModel)
        , m_directionResultReceivedHandler(this, &PathDrawingController::OnSearchQueryResponseReceivedMessage)
        , m_directionsMenuStateChangedCallback(this, &PathDrawingController::OnDirectionsMenuStateChanged)
        , m_onDirectionItemAddedCallback(this, &PathDrawingController::OnSearchItemAdded)
        , m_onDirectionItemRemovedCallback(this, &PathDrawingController::OnSearchItemRemoved)
        , m_onFindNewDirectionCallback(this, &PathDrawingController::OnFindNewDirection)
        {
            m_pPathDrawingSettings = Eegeo_NEW(ExampleApp::PathDrawing::PathDrawingOptionsModel)();
            m_routeThicknessPolicy.SetScaleFactor(1.0f);
            
            m_messageBus.SubscribeUi(m_directionResultReceivedHandler);
            m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
            
            Menu::View::IMenuModel& searchSectionMenuModel = m_searchSectionViewModel.GetModel();
            searchSectionMenuModel.InsertItemAddedCallback(m_onDirectionItemAddedCallback);
            searchSectionMenuModel.InsertItemRemovedCallback(m_onDirectionItemRemovedCallback);
            
            m_messageBus.SubscribeNative(m_onFindNewDirectionCallback);

            
            
        }
        
        PathDrawingController::~PathDrawingController()
        {
            Eegeo_DELETE m_pPathDrawingSettings;
            m_messageBus.UnsubscribeUi(m_directionResultReceivedHandler);
            m_messageBus.UnsubscribeUi(m_directionsMenuStateChangedCallback);
            m_messageBus.UnsubscribeNative(m_onFindNewDirectionCallback);

        }
        
        void PathDrawingController::OnSearchItemAdded(Menu::View::MenuItemModel& item)
        {
            ExampleApp::SearchResultSection::View::SearchResultItemModel &searchItem = (ExampleApp::SearchResultSection::View::SearchResultItemModel&)item.MenuOption();

            Eegeo::Space::LatLong latLongStart = Eegeo::Space::LatLong::FromECEF(searchItem.GetLocationEcef());
            WayPointModel* point = Eegeo_NEW(ExampleApp::PathDrawing::WayPointModel)(searchItem.GetItemIndex()
                                                                         , ExampleApp::PathDrawing::WayPointType::CheckPoint
                                                                         , latLongStart
                                                                         , "");
            m_pWayPointsRepository.AddItem(point);
        }
        
        void PathDrawingController::OnSearchItemRemoved(Menu::View::MenuItemModel& item)
        {

        }

        void PathDrawingController::Update(float dt)
        {
            
            if(m_createdRoutes)
            {
                float altitude = m_cameraWrapper.GetRenderCamera().GetAltitude();
                m_routeThicknessPolicy.SetAltitude(altitude);
            }
            
        }
        
        void PathDrawingController::OnSearchQueryResponseReceivedMessage(const DirectionResultSection::DirectionQueryResponseReceivedMessage& message)
        {
            
            if(!m_createdRoutes)
            {
                Direction::SdkModel::DirectionResultModel& model = message.GetDirectionResultModel();
                CreateRoutePlan(model);
            }
        }
        
        void PathDrawingController::OnFindNewDirection(const DirectionsMenu::DirectionMenuFindDirectionMessage&)
        {
            if(m_createdRoutes)
            {
               RemoveRoutePlan();
            }
        }

        
        void PathDrawingController::CreateRoutePlan(Direction::SdkModel::DirectionResultModel& directionResultModel)
        {

            const std::vector<Direction::SdkModel::DirectionRouteModel>& routes = directionResultModel.GetRoutes();
            if(routes.size() > 0)
            {
                Direction::SdkModel::DirectionRouteModel routeModel = routes[0];
                const std::vector<Direction::SdkModel::DirectionInnerRouteModel>& innerRoutesVector = routeModel.GetInnerRoutes();
                
                for(int i=0; i<innerRoutesVector.size();i++)
                {
                    RouteBuilder builder;
                    Direction::SdkModel::DirectionInnerRouteModel innerRouteModel = innerRoutesVector[i];
                    
                    const Direction::SdkModel::DirectionRouteGeometryModel& innerRouteGeomatry = innerRouteModel.GetInnerRouteGeometry();
                    
                    const std::vector<Eegeo::Space::LatLong>& coordinatesVector = innerRouteGeomatry.GetCoordinates();
                    
                    const float altitudeMeters = m_pPathDrawingSettings->GetRouteAltitudeMeter();
                    
                    Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone);
                    if (i%2 == 0)
                    {
                        builder.Start(m_pPathDrawingSettings->GetRoutePrimaryColor(), m_pPathDrawingSettings->GetRouteWidth(), m_pPathDrawingSettings->GetRouteSpeed(), Routes::Road);
                    }
                    else
                    {
                        builder.Start(m_pPathDrawingSettings->GetRouteSecondaryColor(), m_pPathDrawingSettings->GetRouteWidth(), m_pPathDrawingSettings->GetRouteSpeed(), Routes::Road);
                    }
                                        
                    for (std::vector<Eegeo::Space::LatLong>::const_iterator it = coordinatesVector.begin() ; it != coordinatesVector.end(); ++it)
                    {
                        builder.AddPoint(it->GetLatitudeInDegrees(), it->GetLongitudeInDegrees(), altitudeMeters);
                    }
                    std::vector<RouteVertex> points = builder.FinishRoute();
                    
                    m_routes.push_back(m_routeService.CreateRoute(points, routeStyle, false));
                }
                
            }
            m_createdRoutes = true;
        }
        
        void PathDrawingController::OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message)
        {
            if(message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Inactive)
            {
                RemoveRoutePlan();
            }
        }
        
        void PathDrawingController::RemoveRoutePlan()
        {
            for(std::vector<Route*>::iterator i = m_routes.begin(); i != m_routes.end(); ++ i)
            {
                m_routeService.DestroyRoute(*i);
            }
            
            while (m_pWayPointsRepository.GetItemCount() != 0)
            {
                WayPointModel* waypoint = m_pWayPointsRepository.GetItemAtIndex(0);
                m_pWayPointsRepository.RemoveItem(waypoint);
                Eegeo_DELETE waypoint;
            }
            m_createdRoutes = false;
            m_routes.clear();

        }
        
        bool PathDrawingController::IsRouteCreated()
        {
            return m_createdRoutes;
        }
        
        std::vector<Eegeo::Routes::Route*>& PathDrawingController::GetCreatedRoutes()
        {
            return m_routes;
        }
    }
}

