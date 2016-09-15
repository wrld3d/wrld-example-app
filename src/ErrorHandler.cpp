// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "ErrorHandler.h"

namespace ExampleApp
{
    ErrorHandler::ErrorHandler(const std::shared_ptr<Eegeo::UI::NativeAlerts::IAlertBoxFactory>& alertBoxFactory,
                               const std::shared_ptr<ExampleApp::Net::SdkModel::INetworkCapabilities>& networkCapabilities)
    : m_alertBoxFactory(alertBoxFactory)
    , m_networkCapabilities(networkCapabilities)
    , m_failAlertHandler(this, &ErrorHandler::HandleStartupFailure)
    {
        Eegeo_ASSERT(m_alertBoxFactory != nullptr);
        Eegeo_ASSERT(m_networkCapabilities != nullptr);
    }
    
    void ErrorHandler::HandleFailureToProvideWorkingApiKey()
    {
        m_alertBoxFactory->CreateSingleOptionAlertBox
        (
         "Bad API Key",
         "You must provide a valid API key to the constructor of EegeoWorld. See the readme file for details.",
         m_failAlertHandler
         );
    }
    
    void ErrorHandler::HandleFailureToDownloadBootstrapResources()
    {
        std::string message =
        m_networkCapabilities->StreamOverWifiOnly()
        ? "Unable to download required data! Please ensure you have a Wi-fi connection the next time you attempt to run this application."
        : "Unable to download required data! Please ensure you have an Internet connection the next time you attempt to run this application.";
        
        m_alertBoxFactory->CreateSingleOptionAlertBox("Error", message, m_failAlertHandler);
    }
    
    void ErrorHandler::HandleNoConnectivityWarning()
    {
    }
    
    void ErrorHandler::HandleInvalidConnectivityError()
    {
        m_alertBoxFactory->CreateSingleOptionAlertBox
        (
         "Network error",
         "Unable to access web reliably. Please check your connection is valid & authenticated.",
         m_failAlertHandler
         );
    }
    
    void ErrorHandler::HandleStartupFailure()
    {
        exit(1);
    }
}





