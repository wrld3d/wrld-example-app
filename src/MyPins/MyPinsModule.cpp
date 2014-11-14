// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinsModule.h"
#include "Types.h"
#include "MyPinsRepository.h"
#include "MyPinsFileIO.h"
#include "MyPinsService.h"
#include "LatLongAltitude.h"
#include "IPlatformAbstractionModule.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinsModule::MyPinsModule(Eegeo::Pins::PinRepository& pinRepository,
                                   WorldPins::IWorldPinsFactory& pinFactory,
                                   Eegeo::Modules::IPlatformAbstractionModule& platformAbstractions,
                                   PersistentSettings::IPersistentSettingsModel& persistentSettings)
        : m_pMyPinsRepository(NULL)
        , m_pMyPinsFileIO(NULL)
        , m_pMyPinsService(NULL)
        , m_pMenuModel(NULL)
        , m_pMenuOptionsModel(NULL)
        {
            m_pMenuModel = Eegeo_NEW(Menu::MenuModel)();
            m_pMenuOptionsModel = Eegeo_NEW(Menu::MenuOptionsModel)(*m_pMenuModel);
            
            m_pMyPinsRepository = Eegeo_NEW(MyPinsRepository)();
            m_pMyPinsFileIO = Eegeo_NEW(MyPinsFileIO)(platformAbstractions.GetFileIO(), persistentSettings);
            m_pMyPinsService = Eegeo_NEW(MyPinsService)(*m_pMyPinsRepository,
                                                        *m_pMyPinsFileIO,
                                                        *m_pMenuOptionsModel,
                                                        pinRepository,
                                                        pinFactory,
                                                        platformAbstractions.GetWebLoadRequestFactory());
        }
        
        MyPinsModule::~MyPinsModule()
        {
            Eegeo_DELETE m_pMyPinsService;
            Eegeo_DELETE m_pMyPinsFileIO;
            Eegeo_DELETE m_pMyPinsRepository;
            
            Eegeo_DELETE m_pMenuOptionsModel;
            Eegeo_DELETE m_pMenuModel;
        }
        
        IMyPinsService& MyPinsModule::GetMyPinsService() const
        {
            return *m_pMyPinsService;
        }
    }
}
