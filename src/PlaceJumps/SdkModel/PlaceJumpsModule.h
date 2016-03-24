// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"
#include "IPlaceJumpsModule.h"
#include "Types.h"
#include "PlaceJumps.h"
#include "PlaceJumpsDataParser.h"
#include "IFileIO.h"
#include "CameraTransitions.h"
#include "Compass.h"
#include "BidirectionalBus.h"
#include "PlaceJumpSelectedMessageHandler.h"
#include "IMetricsService.h"
#include "IMenuReactionModel.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace SdkModel
        {
            class PlaceJumpsModule : public IPlaceJumpsModule, private Eegeo::NonCopyable
            {
            public:

                PlaceJumpsModule(Eegeo::Helpers::IFileIO& fileIO,
                                 CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                 Menu::View::IMenuViewModel& menuViewModel,
                                 ExampleAppMessaging::TMessageBus& messageBus,
                                 Metrics::IMetricsService& metricsService,
                                 const Menu::View::IMenuReactionModel& menuReaction);

                ~PlaceJumpsModule();

                Menu::View::IMenuModel& GetPlaceJumpsMenuModel() const
                {
                    return *m_pMenuModel;
                }
                IPlaceJumpController& GetPlaceJumpController() const
                {
                    return *m_pJumpController;
                }

            private:

                Menu::View::IMenuModel* m_pMenuModel;
                Menu::View::IMenuOptionsModel* m_pMenuOptionsModel;
                IPlaceJumpController* m_pJumpController;
                PlaceJumpSelectedMessageHandler* m_pPlaceJumpSelectedMessageHandler;
            };
        }
    }
}
