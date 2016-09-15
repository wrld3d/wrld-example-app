// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Types.h"
#include "IEegeoErrorHandler.h"
#include "IAlertBoxFactory.h"
#include "INetworkCapabilities.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include <memory>

namespace ExampleApp
{
    class ErrorHandler : public Eegeo::IEegeoErrorHandler, private Eegeo::NonCopyable
    {
    public:
        ErrorHandler(const std::shared_ptr<Eegeo::UI::NativeAlerts::IAlertBoxFactory>& alertBoxFactory,
                     const std::shared_ptr<ExampleApp::Net::SdkModel::INetworkCapabilities>& networkCapabilities);
        
        void HandleFailureToProvideWorkingApiKey();
        void HandleFailureToDownloadBootstrapResources();
        void HandleNoConnectivityWarning();
        void HandleInvalidConnectivityError();
        
    private:
        const std::shared_ptr<Eegeo::UI::NativeAlerts::IAlertBoxFactory> m_alertBoxFactory;
        const std::shared_ptr<ExampleApp::Net::SdkModel::INetworkCapabilities> m_networkCapabilities;
        Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<ErrorHandler> m_failAlertHandler;
        
        void HandleStartupFailure();
    };
}