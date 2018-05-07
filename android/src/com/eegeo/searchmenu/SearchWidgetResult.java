// Copyright WRLD Ltd (2018-), All Rights Reserved

package com.eegeo.searchmenu;

import com.wrld.widgets.search.model.DefaultSearchResult;
import com.wrld.widgets.search.model.SearchResultPropertyString;

public class SearchWidgetResult extends DefaultSearchResult
{
	int m_index;

	public SearchWidgetResult(int index, String title, String description, String iconName)
	{
		super(title,
			  new SearchResultPropertyString("Description", description),
			  new SearchResultPropertyString("Icon", iconName));

		m_index = index;
	}

	public int getIndex()
	{
		return m_index;
	}
}