// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ViewControllerUpdater.h"
#include "UpdateProtocol.h"

namespace ExampleApp
{
	namespace ViewControllerUpdater
	{
		class IViewControllerUpdaterModel
		{
		public:
			virtual ~IViewControllerUpdaterModel() { }

			virtual void AddUpdateableObject(id<UpdateProtocol> updateProtocolImplementation) = 0;

			virtual void RemoveUpdateableObject(id<UpdateProtocol> updateProtocolImplementation) = 0;

			virtual void UpdateObjects(float deltaSeconds) = 0;
		};
	}
}
