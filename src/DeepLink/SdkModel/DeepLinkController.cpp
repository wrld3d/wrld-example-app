// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeepLinkController.h"
#include "DeepLinkQueryStringParser.h"

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
                
                IDeepLinkHandler* handler = NULL;
                IDeepLinkHandler* handler2 = NULL; //rename this
                if(data.query != NULL)
                {
                    m_deeplinkQueryStringParser.ParseData(data.query);
                }
                
                if(m_deeplinkQueryStringParser.HasValidQueryString())
                {
                    if(m_deeplinkQueryStringParser.HasMapScene())
                    {
                        handler2 = m_deepLinkModel.Get(std::string(m_deeplinkQueryStringParser.GetMapsceneData(data).host));
                        if(handler2 != NULL)
                            handler2->HandleDeepLink(m_deeplinkQueryStringParser.GetMapsceneData(data));
                    }
                    handler = m_deepLinkModel.Get(std::string(data.host));
                     if(handler != NULL)
                         handler->HandleDeepLink(m_deeplinkQueryStringParser.GetSearchData(data));///test this works
                }
                else
                {
                    handler = m_deepLinkModel.Get(std::string(data.host));
                    if(handler != NULL)
                         handler->HandleDeepLink(data);
                }
            }
        }
    }
}
