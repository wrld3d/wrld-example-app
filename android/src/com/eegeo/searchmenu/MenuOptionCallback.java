package com.eegeo.searchmenu;
import android.util.Log;

//import com.wrld.widgets.searchbox.model.MenuChild;
//import com.wrld.widgets.searchbox.model.MenuGroup;
//import com.wrld.widgets.searchbox.model.MenuOption;
import com.wrld.widgets.searchbox.WrldSearchWidget;
import com.wrld.widgets.searchbox.model.MenuChild;
import com.wrld.widgets.searchbox.model.MenuGroup;
import com.wrld.widgets.searchbox.model.MenuOption;
import com.wrld.widgets.searchbox.model.OnMenuOptionSelectedCallback;
import com.eegeo.menu.MenuViewJniMethods;

import org.json.JSONObject;

import java.util.Arrays;
import java.util.List;

//import org.json.JSONObject;

//import java.util.Arrays;
//import java.util.List;

public class MenuOptionCallback implements OnMenuOptionSelectedCallback {
    protected long m_nativeCallerPointer;
    protected WrldSearchWidget m_searchWidget;
    public MenuOptionCallback(long nativeCallerPointer) {
        m_nativeCallerPointer = nativeCallerPointer;
    }


    public boolean onMenuOptionSelected(final String text, final Object context) {
        MenuIndexPath indexPath = (MenuIndexPath) context;
        MenuViewJniMethods.SelectedItem(m_nativeCallerPointer, indexPath.m_section, indexPath.m_item);
        return true;
    }



    public void populateData(
            final long nativeCallerPointer,
            final String[] optionNames,
            final int[] optionSizes,
            final String[] childJsons) {
        //super.populateData(nativeCallerPointer,optionNames,optionSizes,childJson);
        //m_searchWidget.clearMenu();

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

                childIndex++;

                MenuChild child = new MenuChild(name, iconName, indexPath, this);
                menuOption.addChild(child);
            }

            childIndex++;
        }
        //m_searchWidget.c
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