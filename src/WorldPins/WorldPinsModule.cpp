// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinsModule.h"
#include "WorldPins.h"
#include "WorldPinsFactory.h"
#include "WorldPinsRepository.h"
#include "WorldPinsService.h"
#include "WorldPinsScaleController.h"
#include "WorldPinsInFocusController.h"
#include "WorldPinInFocusViewModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        WorldPinsModule::WorldPinsModule(Eegeo::Pins::PinRepository& pinRepository,
                                         Eegeo::Pins::PinController& pinController,
                                         const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                         const Eegeo::Rendering::ScreenProperties& screenProperties,
                                         Eegeo::Helpers::IIdentityProvider& identityProvider,
                                         ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus,
                                         ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
        {
            m_pWorldPinsFactory = Eegeo_NEW(WorldPinsFactory);
            
            m_pWorldPinsRepository = Eegeo_NEW(WorldPinsRepository);
            
            m_pWorldPinsService = Eegeo_NEW(WorldPinsService)(*m_pWorldPinsRepository,
                                                              *m_pWorldPinsFactory,
                                                              pinRepository,
                                                              pinController,
                                                              environmentFlatteningService);
            
            m_pWorldPinsScaleController = Eegeo_NEW(WorldPinsScaleController)(*m_pWorldPinsRepository,
                                                                              *m_pWorldPinsService,
                                                                              screenProperties,
                                                                              uiToNativeMessageBus);
            
            m_pWorldPinsInFocusViewModel = Eegeo_NEW(WorldPinInFocusViewModel)(identityProvider.GetNextIdentity(),
                                                                               *m_pWorldPinsService);
            
            m_pWorldPinsInFocusController = Eegeo_NEW(WorldPinsInFocusController)(*m_pWorldPinsRepository,
                                                                                  *m_pWorldPinsService,
                                                                                  nativeToUiMessageBus,
                                                                                  uiToNativeMessageBus);
            
            
            m_pWorldPinInFocusObserver = Eegeo_NEW(WorldPinInFocusObserver)(*m_pWorldPinsInFocusViewModel,
                                                                            nativeToUiMessageBus);
            
            m_pWorldPinsModalityObserver = Eegeo_NEW(WorldPinsModalityObserver)(*m_pWorldPinsScaleController,
                                                                                uiToNativeMessageBus);
            
            
        }
        
        WorldPinsModule::~WorldPinsModule()
        {
            Eegeo_DELETE m_pWorldPinsModalityObserver;
            Eegeo_DELETE m_pWorldPinInFocusObserver;
            Eegeo_DELETE m_pWorldPinsInFocusController;
            Eegeo_DELETE m_pWorldPinsInFocusViewModel;
            Eegeo_DELETE m_pWorldPinsScaleController;
            Eegeo_DELETE m_pWorldPinsService;
            Eegeo_DELETE m_pWorldPinsRepository;
            Eegeo_DELETE m_pWorldPinsFactory;
        }
        
        IWorldPinsService& WorldPinsModule::GetWorldPinsService() const
        {
            return *m_pWorldPinsService;
        }
        
        IWorldPinsFactory& WorldPinsModule::GetWorldPinsFactory() const
        {
            return *m_pWorldPinsFactory;
        }
        
        IWorldPinsScaleController& WorldPinsModule::GetWorldPinsScaleController() const
        {
            return *m_pWorldPinsScaleController;
        }
        
        IWorldPinInFocusViewModel& WorldPinsModule::GetWorldPinInFocusViewModel() const
        {
            return *m_pWorldPinsInFocusViewModel;
        }
        
        IWorldPinsInFocusController& WorldPinsModule::GetWorldPinsInFocusController() const
        {
            return *m_pWorldPinsInFocusController;
        }
        
        ScreenControlViewModel::IScreenControlViewModel& WorldPinsModule::GetScreenControlViewModel() const
        {
            return m_pWorldPinsInFocusViewModel->GetScreenControlViewModel();
        }
    }
}
