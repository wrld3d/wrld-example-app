// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "TagCollection.h"

namespace ExampleApp
{
	namespace SearchMenu
	{
		namespace View
		{
			TagCollection::TagCollection(ExampleAppMessaging::TMessageBus& messageBus)
			: m_messageBus(messageBus)
			, m_onTagSearchAddedHandler(this, &TagCollection::OnTagSearchAdded)
			, m_onTagSearchRemovedHandler(this, &TagCollection::OnTagSearchRemoved)
			, m_freeStorage(FREE_LIST_END)
			{
				m_messageBus.SubscribeUi(m_onTagSearchAddedHandler);
				m_messageBus.SubscribeUi(m_onTagSearchRemovedHandler);
			}

			TagCollection::~TagCollection()
			{
				m_messageBus.UnsubscribeUi(m_onTagSearchRemovedHandler);
				m_messageBus.UnsubscribeUi(m_onTagSearchAddedHandler);
			}

			void TagCollection::OnTagSearchAdded(const TagSearch::TagSearchAddedMessage& message)
			{
				const TagSearch::View::TagSearchModel& tagSearchModel = message.Model();

				AddTag(tagSearchModel.Name(), tagSearchModel.SearchTag(),
				       tagSearchModel.Interior());
			}

			void TagCollection::OnTagSearchRemoved(const TagSearch::TagSearchRemovedMessage& message)
			{
				const TagSearch::View::TagSearchModel& tagSearchModel = message.Model();

				RemoveTag(tagSearchModel.Name(), tagSearchModel.SearchTag());
			}

			void TagCollection::AddTag(const std::string& text, const std::string& tag,
			                           bool shouldTryInterior)
			{
				Eegeo_ASSERT(m_tagsByText.find(text) == m_tagsByText.end());
				Eegeo_ASSERT(m_tagsByTag .find(tag)  == m_tagsByTag .end());

				TagInfo info(tag, text, shouldTryInterior);
				int     pos;

				if (m_freeStorage == FREE_LIST_END)
				{
					pos = (int)m_tagStorage.size();

					m_tagStorage.push_back(info);
				}
				else
				{
					pos = m_freeStorage;

					TagInfo* storagePlace = &m_tagStorage[m_freeStorage];

					m_freeStorage = storagePlace->m_freeChain;
					*storagePlace = info;
				}

				m_tagsByText[text] = pos;
				m_tagsByTag [tag]  = pos;
			}

			void TagCollection::RemoveTag(const std::string& text, const std::string& tag)
			{
				Eegeo_ASSERT(m_tagsByText.find(text) != m_tagsByText.end());
				Eegeo_ASSERT(m_tagsByTag .find(tag)  != m_tagsByTag .end());

				Eegeo_ASSERT(m_tagsByText[text] == m_tagsByTag[tag]);

				int index = m_tagsByText[text];

				m_tagStorage[index].m_freeChain = m_freeStorage;
				m_freeStorage = index;

				m_tagsByText.erase(text);
				m_tagsByTag .erase(tag);
			}

            bool TagCollection::HasTag(const std::string& text)
            {
                return m_tagsByText.find(text) != m_tagsByText.end();
            }

            bool TagCollection::HasText(const std::string& tag)
            {
                return m_tagsByTag.find(tag) != m_tagsByTag.end();
            }

			const TagCollection::TagInfo& TagCollection::GetInfoByText(const std::string& text)
			{
				TTagTextMap::iterator it = m_tagsByText.find(text);
				Eegeo_ASSERT(it != m_tagsByText.end());

				return m_tagStorage[it->second];
			}

			const TagCollection::TagInfo& TagCollection::GetInfoByTag(const std::string& tag)
			{
				TTagTextMap::iterator it = m_tagsByTag.find(tag);
				Eegeo_ASSERT(it != m_tagsByTag.end());

				return m_tagStorage[it->second];
			}
		}
	}
}
