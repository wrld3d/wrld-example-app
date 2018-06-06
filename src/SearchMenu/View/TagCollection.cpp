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
				if (FindIndex(&text, &tag) >= 0)
				{
					return;
				}

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
			}

			void TagCollection::RemoveTag(const std::string& text, const std::string& tag)
			{
				int index = FindIndex(&text, &tag);

				if (index < 0)
				{
					return;
				}

				m_tagStorage[index].m_freeChain = m_freeStorage;
				m_freeStorage = index;
			}

			int TagCollection::FindIndex(const std::string* text, const std::string* tag)
			{
				const void* WILDCARD = NULL;

				for (int pos = 0; pos < m_tagStorage.size(); pos++)
				{
					const TagInfo& info = m_tagStorage[pos];

					if (info.m_freeChain != IN_USE)
					{
						continue;
					}

					if ((text == WILDCARD || *text == info.VisibleText()) &&
					    (tag  == WILDCARD || *tag  == info.Tag()))
					{
						return pos;
					}
				}

				return -1;
			}

            bool TagCollection::HasTag(const std::string& text)
            {
                return FindIndex(&text, NULL) >= 0;
            }

            bool TagCollection::HasText(const std::string& tag)
            {
				return FindIndex(NULL, &tag) >= 0;
            }

			const TagCollection::TagInfo& TagCollection::GetInfoByText(const std::string& text)
			{
				int index = FindIndex(&text, NULL);
				Eegeo_ASSERT(index >= 0);

				return m_tagStorage[index];
			}

			const TagCollection::TagInfo& TagCollection::GetInfoByTag(const std::string& tag)
			{
				int index = FindIndex(NULL, &tag);
				Eegeo_ASSERT(index >= 0);

				return m_tagStorage[index];
			}
		}
	}
}
