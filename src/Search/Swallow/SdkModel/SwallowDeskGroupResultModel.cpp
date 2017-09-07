// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowDeskGroupResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowDeskGroupResultModel::SwallowDeskGroupResultModel(const std::string& name,
                                                                         const std::vector<std::string>& desks)
                : m_name(name)
                , m_desks(desks)
                {
                    
                }
                
                SwallowDeskGroupResultModel::SwallowDeskGroupResultModel()
                {
                }
                
                SwallowDeskGroupResultModel::~SwallowDeskGroupResultModel()
                {
                }
                
                const std::string& SwallowDeskGroupResultModel::GetName() const
                {
                    return m_name;
                }

                const std::vector<std::string>& SwallowDeskGroupResultModel::GetAllDesks() const
                {
                    return m_desks;
                }
            }
        }
    }
}