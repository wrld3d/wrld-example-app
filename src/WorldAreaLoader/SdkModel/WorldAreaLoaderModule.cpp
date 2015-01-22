// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldAreaLoaderModule.h"
#include "WorldAreaLoader.h"
#include "WorldAreaLoaderModel.h"

namespace ExampleApp
{
    namespace WorldAreaLoader
    {
        namespace SdkModel
        {
            WorldAreaLoaderModule::WorldAreaLoaderModule(Eegeo::Web::PrecacheService& precacheService)
            {
                WorldAreaLoaderModel* pModel = Eegeo_NEW(WorldAreaLoaderModel)(precacheService);
                m_pWorldAreaLoaderModel = pModel;
            }

            WorldAreaLoaderModule::~WorldAreaLoaderModule()
            {
                Eegeo_DELETE m_pWorldAreaLoaderModel;
            }

            IWorldAreaLoaderModel& WorldAreaLoaderModule::GetWorldAreaLoaderModel() const
            {
                return *m_pWorldAreaLoaderModel;
            }
        }
    }
}
