// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.searchmenu;

import com.eegeo.entrypointinfrastructure.MainActivity;
import com.eegeo.ProjectSwallowApp.R;

import android.util.Log;
import android.view.View;
import android.widget.RelativeLayout;

import com.eegeo.menu.MenuViewJniMethods;
import com.eegeo.tags.TagResources;
import com.wrld.widgets.searchbox.WrldSearchWidget;
import com.wrld.widgets.searchbox.model.MenuChild;
import com.wrld.widgets.searchbox.model.MenuGroup;
import com.wrld.widgets.searchbox.model.MenuOption;
import com.wrld.widgets.searchbox.model.OnMenuOptionSelectedCallback;
import com.wrld.widgets.searchbox.model.SearchProvider;

import org.json.JSONObject;

import java.util.Arrays;
import java.util.List;

public class SearchWidgetView implements OnMenuOptionSelectedCallback
{
    protected MainActivity m_activity;
    protected SearchProvider m_searchProvider;
    protected long m_nativeCallerPointer;
    protected View m_view;

    protected WrldSearchWidget m_searchWidget;

    public SearchWidgetView(MainActivity activity, long nativeCallerPointer,
                            SearchProvider searchProvider)
    {
        m_activity = activity;
        m_searchProvider = searchProvider;
        m_nativeCallerPointer = nativeCallerPointer;

        createView();
    }

    protected void createView()
    {
        final RelativeLayout uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);
        m_view = m_activity.getLayoutInflater().inflate(R.layout.search_widget_view_layout, uiRoot, false);
        uiRoot.addView(m_view);

        m_searchWidget = (WrldSearchWidget) m_activity.getFragmentManager().findFragmentById(R.id.search_widget);
        m_searchWidget.addSearchProvider(m_searchProvider);
    }



    public boolean onMenuOptionSelected(final String text, final Object context) {
        MenuIndexPath indexPath = (MenuIndexPath) context;
       //SeacrhWidgetJniMethods.SelectedItem(m_nativeCallerPointer, indexPath.m_section, indexPath.m_item);
        return true;
    }


    public void populateData(
            final long nativeCallerPointer,
            final String[] optionNames,
            final int[] optionSizes,
            final String[] childJsons) {

        m_searchWidget.clearMenu();

        MenuGroup menuGroup = new MenuGroup("Show me the closest...");

        List<String> options = Arrays.asList(optionNames);
        int childIndex = 1;

        int[] groupSizes = {5, 2, 1, 2};
        int numberOfGroups = 4;
        int groupIndex = 0;
        int maxOptionIndexForGroup = groupSizes[0];

        for (int optionIndex = 0; optionIndex < options.size(); optionIndex++) {
            if (optionIndex == maxOptionIndexForGroup && groupIndex < numberOfGroups - 1) {
                groupIndex++;
                maxOptionIndexForGroup += groupSizes[groupIndex];
                m_searchWidget.addMenuGroup(menuGroup);
                menuGroup = new MenuGroup();
            }

            int sizeWithoutHeader = optionSizes[optionIndex] - 1;

            String optionName = getFromJson(optionNames[optionIndex], "name");
            MenuIndexPath optionIndexPath = new MenuIndexPath(optionIndex, 0);
            MenuOption menuOption = new MenuOption(optionName, optionIndexPath, this);

            menuGroup.addOption(menuOption);

            for (int i = 1; i < sizeWithoutHeader; ++i) {
                MenuIndexPath indexPath = new MenuIndexPath(groupIndex, i);
                String childJson = childJsons[childIndex];
                String name = getFromJson(childJson, "name");
                String iconName = getFromJson(childJson, "icon");
                int iconNumber = TagResources.getIconForResourceName(m_activity,iconName);
                MenuChild child = new MenuChild(name,iconNumber, indexPath, this);
                menuOption.addChild(child);
                childIndex++;
            }

            childIndex++;
        }



        m_searchWidget.addMenuGroup(menuGroup);

    }

    private String getFromJson(String jsonString, String tag) {
        try {
            JSONObject json = new JSONObject(jsonString);
            String name = json.getString(tag);
            return name;
        } catch (Exception e) {
            Log.e("MenuView", String.format("Unable to parse %s from group JSON: %s", tag, e.toString()));
            return null;
        }
    }
}
