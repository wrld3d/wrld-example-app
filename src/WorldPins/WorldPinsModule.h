// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IWorldPinsModule.h"
#include "WorldPins.h"
#include "Pins.h"
#include "PinController.h"
#include "Rendering.h"

namespace ExampleApp
{
namespace WorldPins
{
class WorldPinsModule : public IWorldPinsModule
{
	IWorldPinsFactory* m_pWorldPinsFactory;
	IWorldPinsService* m_pWorldPinsService;
	IWorldPinsRepository* m_pWorldPinsRepository;

public:
	WorldPinsModule(Eegeo::Pins::PinRepository& pinRepository,
	                Eegeo::Pins::PinController& pinController,
	                const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService);

	~WorldPinsModule();

	IWorldPinsService& GetWorldPinsService() const;
};
}
}
