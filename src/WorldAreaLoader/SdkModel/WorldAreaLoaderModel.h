// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Web.h"
#include "ICallback.h"
#include "IWorldAreaLoaderModel.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace WorldAreaLoader
    {
        namespace SdkModel
        {
            class WorldAreaLoaderModel : public IWorldAreaLoaderModel, private Eegeo::NonCopyable
            {
                Eegeo::Web::PrecacheService& m_precacheService;
                bool m_preloadInProgress;
                Eegeo::Helpers::CallbackCollection0 m_preloadStartedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_preloadCompletedCallbacks;
                Eegeo::Helpers::ICallback0* m_preloadCompletedCallback;
                Eegeo::Helpers::ICallback0* m_preloadCancelledCallback;

                void ObserveUnderlyingService();

                void HandlePreloadServiceEvent();

            public:
                WorldAreaLoaderModel(Eegeo::Web::PrecacheService& precacheService);

                ~WorldAreaLoaderModel();

                float PercentCompleted() const;

                bool CurrentlyPreloading() const;

                bool IsCancelling() const;

                bool CanPreload(double altitude) const;

                void CancelPreload();

                void PreloadResourcesInVolume(Eegeo::Streaming::IStreamingVolume& volume);

                void InsertPreloadStartedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemovePreloadStartedCallback(Eegeo::Helpers::ICallback0& callback);

                void InsertPreloadCompleteCallback(Eegeo::Helpers::ICallback0& callback);

                void RemovePreloadCompleteCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
