// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinsModule.h"
#include "WorldPins.h"
#include "WorldPinsFactory.h"
#include "WorldPinsRepository.h"
#include "WorldPinsService.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		WorldPinsModule::WorldPinsModule(Eegeo::Pins::PinRepository& pinRepository,
		                                 Eegeo::Pins::PinController& pinController,
		                                 const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService)
		{
			m_pWorldPinsFactory = Eegeo_NEW(WorldPinsFactory);

			m_pWorldPinsRepository = Eegeo_NEW(WorldPinsRepository);

			m_pWorldPinsService = Eegeo_NEW(WorldPinsService)(*m_pWorldPinsRepository,
			                      *m_pWorldPinsFactory,
			                      pinRepository,
			                      pinController,
			                      environmentFlatteningService);
		}

		WorldPinsModule::~WorldPinsModule()
		{
			Eegeo_DELETE m_pWorldPinsService;
			Eegeo_DELETE m_pWorldPinsRepository;
			Eegeo_DELETE m_pWorldPinsFactory;
		}

		IWorldPinsService& WorldPinsModule::GetWorldPinsService() const
		{
			return *m_pWorldPinsService;
		}
	}
}
