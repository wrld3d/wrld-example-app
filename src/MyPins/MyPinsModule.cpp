// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinsModule.h"
#include "Types.h"
#include "MyPinsRepository.h"
#include "MyPinsFileIO.h"
#include "MyPinsService.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinsModule::MyPinsModule(Eegeo::Pins::PinRepository& pinRepository,
                                   WorldPins::IWorldPinsFactory& pinFactory,
                                   Eegeo::Helpers::IFileIO& fileIO)
        : m_pMyPinsRepository(NULL)
        , m_pMyPinsFileIO(NULL)
        , m_pMyPinsService(NULL)
        {
            m_pMyPinsRepository = Eegeo_NEW(MyPinsRepository)();
            m_pMyPinsFileIO = Eegeo_NEW(MyPinsFileIO)(fileIO);
            m_pMyPinsService = Eegeo_NEW(MyPinsService)(*m_pMyPinsRepository,
                                                        *m_pMyPinsFileIO,
                                                        pinRepository,
                                                        pinFactory);
        
        }
        
        MyPinsModule::~MyPinsModule()
        {
            Eegeo_DELETE m_pMyPinsService;
            Eegeo_DELETE m_pMyPinsFileIO;
            Eegeo_DELETE m_pMyPinsRepository;
        }
        
        IMyPinsService& MyPinsModule::GetMyPinsService() const
        {
            return *m_pMyPinsService;
        }
    }
}
