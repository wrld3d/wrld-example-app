// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsResultSectionModule.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "SearchResultSection.h"
#include "SearchResultSectionOrder.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace SdkModel
        {
        
            DirectionsResultSectionModule::DirectionsResultSectionModule(Menu::View::IMenuViewModel& searchMenuViewModel,
                                          Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                          Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                          CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                          const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                          const Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& interiorMarkerRepository,
                                          AppCamera::SdkModel::IAppCameraController& appCameraController,
                                          ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pModel = Eegeo_NEW(Menu::View::MenuModel)();
                
                m_pMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pModel);
                
                m_pSearchResultRepositoryObserver = Eegeo_NEW(ExampleApp::SearchResultSection::View::SearchResultRepositoryObserver)(searchResultRepository,
                                                                                                                                     messageBus);
                
                m_pSearchResultSectionItemSelectedMessageHandler = Eegeo_NEW(SearchResultSection::SdkModel::SearchResultSectionItemSelectedMessageHandler)(cameraTransitionController,
                                                                                                                            messageBus);
                
                m_pSearchResultViewClearedObserver = Eegeo_NEW(SearchResultSection::SdkModel::SearchResultViewClearedObserver)(searchQueryPerformer, messageBus);
                
                m_pSearchResultSectionOrder = Eegeo_NEW(ExampleApp::SearchResultSection::View::SearchResultSectionOrder)();
            
            }
            
            DirectionsResultSectionModule::~DirectionsResultSectionModule()
            {
                Eegeo_DELETE m_pSearchResultSectionOrder;
                Eegeo_DELETE m_pSearchResultViewClearedObserver;
                Eegeo_DELETE m_pSearchResultSectionItemSelectedMessageHandler;
                Eegeo_DELETE m_pSearchResultRepositoryObserver;
                Eegeo_DELETE m_pMenuOptionsModel;
                Eegeo_DELETE m_pModel;
            }
            
            Menu::View::IMenuOptionsModel& DirectionsResultSectionModule::GetDirectionsResultSectionOptionsModel() const
            {
                return *m_pMenuOptionsModel;
            }
            
            Menu::View::IMenuModel& DirectionsResultSectionModule::GetDirectionsResultSectionModel() const
            {
                return *m_pModel;
            }
            
            ExampleApp::SearchResultSection::View::ISearchResultSectionOrder& DirectionsResultSectionModule::GetSearchResultSectionOrder() const
            {
                return *m_pSearchResultSectionOrder;
            }
        
        }
    }
}