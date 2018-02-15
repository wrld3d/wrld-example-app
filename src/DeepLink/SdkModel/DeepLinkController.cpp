// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkController.h"


namespace ExampleApp
{
    namespace DeepLink
    {
        namespace SdkModel
        {
            DeepLinkController::DeepLinkController(DeepLinkModel& deepLinkModel, FlattenButton::SdkModel::IFlattenButtonModel& flattenButtonModel)
            :m_deepLinkModel(deepLinkModel)
            ,m_flattenButtonModel(flattenButtonModel)
            {
            }
            
            DeepLinkController::~DeepLinkController()
            {
            }
            
            void DeepLinkController::HandleDeepLinkOpen(const AppInterface::UrlData& data)
            {
                if(m_flattenButtonModel.GetFlattened())
                {
                    m_flattenButtonModel.Unflatten();
                }
                
                IDeepLinkHandler* handler = m_deepLinkModel.Get(std::string(data.host));
                if(handler != NULL)
                {
                     handler->HandleDeepLink(data);
                }
            }
        }
    }
}
