// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldAreaLoader.h"
#include "Streaming.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace WorldAreaLoader
    {
        namespace SdkModel
        {
            class IWorldAreaLoaderModel
            {
            public:
                virtual ~IWorldAreaLoaderModel() {}

                virtual float PercentCompleted() const = 0;

                virtual bool CurrentlyPreloading() const = 0;

                virtual bool IsCancelling() const = 0;

                virtual void CancelPreload() = 0;

                virtual bool CanPreload(double altitude) const = 0;

                virtual void PreloadResourcesInVolume(Eegeo::Streaming::IStreamingVolume& volume) = 0;

                virtual void InsertPreloadStartedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void RemovePreloadStartedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertPreloadCompleteCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void RemovePreloadCompleteCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
