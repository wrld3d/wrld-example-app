// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IWorldAreaLoaderModule.h"
#include "WorldAreaLoader.h"
#include "Web.h"

namespace ExampleApp
{
namespace WorldAreaLoader
{
class WorldAreaLoaderModule : public IWorldAreaLoaderModule
{
	IWorldAreaLoaderModel* m_pWorldAreaLoaderModel;

public:
	WorldAreaLoaderModule(Eegeo::Web::PrecacheService& precacheService);

	~WorldAreaLoaderModule();

	IWorldAreaLoaderModel& GetWorldAreaLoaderModel() const;
};
}
}
