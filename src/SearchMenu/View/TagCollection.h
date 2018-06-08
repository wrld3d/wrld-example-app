// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "CallbackCollection.h"
#include "TagSearchAddedMessage.h"
#include "TagSearchRemovedMessage.h"

#include <string>
#include <vector>
#include <map>

namespace ExampleApp
{
	namespace SearchMenu
	{
		namespace View
		{
			class TagCollection
			{
			public:
				class TagInfo
				{
					friend class TagCollection;

					int m_freeChain;
					std::string m_tag;
					std::string m_visibleText;
					bool m_shouldTryInterior;
				public:
					TagInfo(const std::string& tag, const std::string& visibleText,
							bool shouldTryInterior)
							: m_freeChain(IN_USE)
							, m_tag(tag)
							, m_visibleText(visibleText)
							, m_shouldTryInterior(shouldTryInterior)
					{
					}
					const std::string& Tag()         const { return m_tag; }
					const std::string& VisibleText() const { return m_visibleText; }
					bool ShouldTryInterior()         const { return m_shouldTryInterior; }
				};

			private:
				ExampleAppMessaging::TMessageBus& m_messageBus;

				std::vector<TagInfo> m_tagStorage;
				int m_freeStorage;
				static const int FREE_LIST_END = -1;
				static const int IN_USE = -2;

				Eegeo::Helpers::TCallback1<TagCollection, const TagSearch::TagSearchAddedMessage&> m_onTagSearchAddedHandler;
				Eegeo::Helpers::TCallback1<TagCollection, const TagSearch::TagSearchRemovedMessage&> m_onTagSearchRemovedHandler;

				void OnTagSearchAdded(const TagSearch::TagSearchAddedMessage& message);
				void OnTagSearchRemoved(const TagSearch::TagSearchRemovedMessage& message);
				void AddTag(const std::string& text, const std::string& tag,
				            bool shouldTryInterior);
				void RemoveTag(const std::string& text, const std::string& tag);
				int FindIndex(const std::string* text, const std::string* tag);

			public:
				TagCollection(ExampleAppMessaging::TMessageBus& messageBus);
				~TagCollection();

                bool HasTag(const std::string& text);
                bool HasText(const std::string& tag);
				const TagInfo& GetInfoByText(const std::string& text);
				const TagInfo& GetInfoByTag(const std::string& tag);
			};
		}
	}
}
