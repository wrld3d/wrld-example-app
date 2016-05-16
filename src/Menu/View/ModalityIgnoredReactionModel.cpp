// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuSectionViewModel.h"
#include "IMenuModel.h"
#include "MenuJsonSerializer.h"
#include "ModalityIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            ModalityIgnoredReactionModel::ModalityIgnoredReactionModel()
            {
            }

            ModalityIgnoredReactionModel::~ModalityIgnoredReactionModel()
            {
            }

            void ModalityIgnoredReactionModel::AddIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity)
            {
                m_ignoredMenuIdentities.push_back(identity);
            }

            bool ModalityIgnoredReactionModel::RemoveIgnoredMenuIdentity(Eegeo::Helpers::TIdentity identity)
            {
                std::vector<Eegeo::Helpers::TIdentity>::iterator result = std::find(m_ignoredMenuIdentities.begin(), m_ignoredMenuIdentities.end(), identity);

                if (result == m_ignoredMenuIdentities.end())
                {
                    return false;
                }

                m_ignoredMenuIdentities.erase(result);

                return true;
            }

            bool ModalityIgnoredReactionModel::IsIgnored(Eegeo::Helpers::TIdentity identity) const
            {
                std::vector<Eegeo::Helpers::TIdentity>::const_iterator result = std::find(m_ignoredMenuIdentities.begin(), m_ignoredMenuIdentities.end(), identity);

                if (result == m_ignoredMenuIdentities.end())
                {
                    return false;
                }

                return true;
            }
        }
    }
}
