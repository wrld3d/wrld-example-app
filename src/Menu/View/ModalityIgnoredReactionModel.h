// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IMenuIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            class ModalityIgnoredReactionModel : public IMenuIgnoredReactionModel
            {
                std::vector<Eegeo::Helpers::TIdentity> m_ignoredMenuIdentities;
            public:
                ModalityIgnoredReactionModel();
                ~ModalityIgnoredReactionModel();

                void AddIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity);
                bool RemoveIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity);

                bool IsIgnored(Eegeo::Helpers::TIdentity identity) const;
            };
        }
    }
}
