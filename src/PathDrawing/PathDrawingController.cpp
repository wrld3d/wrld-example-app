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
        {
            m_pPathDrawingSettings = Eegeo_NEW(ExampleApp::PathDrawing::PathDrawingOptionsModel)();
            m_routeThicknessPolicy.SetScaleFactor(1.0f);
            
            m_messageBus.SubscribeUi(m_directionResultReceivedHandler);
            m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
            
            Menu::View::IMenuModel& searchSectionMenuModel = m_searchSectionViewModel.GetModel();
            searchSectionMenuModel.InsertItemAddedCallback(m_onDirectionItemAddedCallback);
            searchSectionMenuModel.InsertItemRemovedCallback(m_onDirectionItemRemovedCallback);
            
            
        }
        
        PathDrawingController::~PathDrawingController()
        {
            Eegeo_DELETE m_pPathDrawingSettings;
            m_messageBus.UnsubscribeUi(m_directionResultReceivedHandler);
            m_messageBus.UnsubscribeUi(m_directionsMenuStateChangedCallback);

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
        
        void PathDrawingController::CreateRoutePlan(Direction::SdkModel::DirectionResultModel& directionResultModel)
        {
  //          const float altitudeMeters = m_pPathDrawingSettings->GetRouteAltitudeMeter();;
            
//            Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone);
//            
//            RouteBuilder builder;
//            
//            std::vector<RouteVertex> points = builder.Start(m_pPathDrawingSettings->GetRoutePrimaryColor(), m_pPathDrawingSettings->GetRouteWidth(), m_pPathDrawingSettings->GetRouteSpeed(), Routes::Road)
//            .AddPoint(56.459676, -2.977240, altitudeMeters)
//            .AddPoint(56.459178, -2.975524, altitudeMeters)
//            .AddPoint(56.458467, -2.973764, altitudeMeters)
//            .AddPoint(56.457827, -2.972691, altitudeMeters)
//            .AddPoint(56.457779, -2.971833, altitudeMeters)
//            .AddPoint(56.457771, -2.971389, altitudeMeters)
//            .AddPoint(56.457860, -2.970793, altitudeMeters)
//            .AddPoint(56.458822, -2.968892, altitudeMeters)
//            .AddPoint(56.461725, -2.964054, altitudeMeters)
//            .AddPoint(56.461547, -2.963546, altitudeMeters)
//            .AddPoint(56.461427, -2.963596, altitudeMeters)
//            .AddPoint(56.461369, -2.963540, altitudeMeters)
//            .AddPoint(56.460882, -2.962729, altitudeMeters)
//            .FinishRoute();
//            
//            m_routes.push_back(m_routeService.CreateRoute(points, routeStyle, false));
            
            
            const std::vector<Direction::SdkModel::DirectionRouteModel>& routes = directionResultModel.GetRoutes();
            if(routes.size() > 0)
            {
                Direction::SdkModel::DirectionRouteModel routeModel = routes[0];
                const std::vector<Direction::SdkModel::DirectionInnerRouteModel>& innerRoutesVector = routeModel.GetInnerRoutes();
                
                for(int i=0; i<1;i++)
                {
                    RouteBuilder builder;

                    Direction::SdkModel::DirectionInnerRouteModel innerRouteModel = innerRoutesVector[i];
                    
                    const Direction::SdkModel::DirectionRouteGeometryModel& innerRouteGeomatry = innerRouteModel.GetInnerRouteGeometry();
                    
                    const std::vector<Eegeo::Space::LatLong>& coordinatesVector = innerRouteGeomatry.GetCoordinates();
                    
                    const float altitudeMeters = m_pPathDrawingSettings->GetRouteAltitudeMeter();
                    
                    Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone);
                    

                    builder.Start(m_pPathDrawingSettings->GetRoutePrimaryColor(), m_pPathDrawingSettings->GetRouteWidth(), m_pPathDrawingSettings->GetRouteSpeed(), Routes::Road);
                    
                    for (std::vector<Eegeo::Space::LatLong>::const_iterator it = coordinatesVector.begin() ; it != coordinatesVector.end(); ++it)
                    {
                        builder.AddPoint(it->GetLatitudeInDegrees(), it->GetLongitudeInDegrees(), altitudeMeters);
                    }
                    std::vector<RouteVertex> points = builder.FinishRoute();
                    
                    m_routes.push_back(m_routeService.CreateRoute(points, routeStyle, false));

                }
                
                
                
                
                
                
              //  std::vector<RouteVertex> otherPoints = builder.Start(m_pPathDrawingSettings->GetRouteSecondaryColor(), m_pPathDrawingSettings->GetRouteWidth(), m_pPathDrawingSettings->GetRouteSpeed(), Routes::Road)

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
            
            m_routes.clear();
            
            while (m_pWayPointsRepository.GetItemCount() != 0)
            {
                WayPointModel* waypoint = m_pWayPointsRepository.GetItemAtIndex(0);
                m_pWayPointsRepository.RemoveItem(waypoint);
                Eegeo_DELETE waypoint;
            }
           m_createdRoutes = false;
        }
    }
}

