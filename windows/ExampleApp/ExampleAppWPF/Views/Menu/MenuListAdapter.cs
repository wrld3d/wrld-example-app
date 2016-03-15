using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;

namespace ExampleAppWPF
{
    public class MenuListAdapter
    {
        private List<string> m_groups;
        private List<bool> m_groupsExpandable;
        private Dictionary<string, List<string>> m_groupToChildrenMap;
        
        private Dictionary<string, int> m_animatedSizesMap;
        private bool m_shouldAlignIconRight;

        private StoryboardRunner m_fadeInStoryboardRunner;
        private StoryboardRunner m_fadeOutStoryboardRunner;
        private StoryboardRunner m_slideInStoryboardRunner;
        private StoryboardRunner m_slideOutStoryboardRunner;

        private ListBox m_list;

        private readonly string ControlToAnimate;

        public MenuListAdapter(bool shouldAlignIconRight, ListBox list,
            Storyboard slideInAnimation, Storyboard slideOutAnimation, Storyboard fadeInItemAnimation, Storyboard fadeOutItemAnimation, string controlToAnimate)
        {   
            m_animatedSizesMap = new Dictionary<string, int>();

            m_groups = new List<string>();
            m_groupsExpandable = new List<bool>();
            m_groupToChildrenMap = new Dictionary<string, List<string>>();

            m_shouldAlignIconRight = shouldAlignIconRight;
            m_children = new ObservableCollection<MenuListItem>();

            m_list = list;

            m_fadeInStoryboardRunner = new StoryboardRunner(fadeInItemAnimation);
            m_fadeOutStoryboardRunner = new StoryboardRunner(fadeOutItemAnimation);
            m_slideInStoryboardRunner = new StoryboardRunner(slideInAnimation);
            m_slideOutStoryboardRunner = new StoryboardRunner(slideOutAnimation);

            ControlToAnimate = controlToAnimate;
        }

        public bool IsAnimating()
        {
            return m_fadeInStoryboardRunner.IsAnimating ||
                m_fadeOutStoryboardRunner.IsAnimating ||
                m_slideInStoryboardRunner.IsAnimating ||
                m_slideOutStoryboardRunner.IsAnimating;
        }

        public void ResetData()
        {
            m_animatedSizesMap.Clear();

            m_groups.Clear();
            m_groupsExpandable.Clear();
            m_groupToChildrenMap.Clear();

            m_children.Clear();
        }

        public void SetData(
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren)
        {
            if (m_groups.Count != groups.Count)
            {
                UpdateSources(groups, groupsExpandable, groupToChildren);
                ForceSetAnimatedSizes();
                NotifyDataSetChanged();
            }
            else
            {
                UpdateAndAnimateSources(groups, groupsExpandable, groupToChildren);
            }
        }

        public void UpdateSources(
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren)
        {
            m_groups = groups;
            m_groupsExpandable = groupsExpandable;
            m_groupToChildrenMap = groupToChildren;
        }

        public void ForceSetAnimatedSizes()
        {
            for (int groupIndex = 0; groupIndex < m_groups.Count; groupIndex++)
            {
                var key = m_groups[groupIndex];
                m_animatedSizesMap[key] = m_groupToChildrenMap[key].Count;
            }
        }
        public void SetAnimatedGroupSize(string groupName, int size)
        {
            if (!m_animatedSizesMap.ContainsKey(groupName))
            {
                throw new ArgumentException("No group named " + groupName + " found!");
            }

            int oldSize = m_animatedSizesMap[groupName];

            if (oldSize != size)
            {
                m_animatedSizesMap[groupName] = size;

                NotifyDataSetChanged();
            }
        }
        public void NotifyDataSetChanged()
        {
            m_children.Clear();
            int overAllItemIndex = 0;
            int totalCount = m_animatedSizesMap.Values.Sum();
            int lastMenuGroupIndex = -1;

            for (int i = 0; i < m_groups.Count; i++)
            {
                int groupIndex = i;
                string groupName = m_groups[groupIndex];
                int currentSize = m_animatedSizesMap[groupName];

                if(currentSize != 0 && i == (m_groups.Count - 1))
                {
                    lastMenuGroupIndex = overAllItemIndex;
                }

                for (int itemIndex = 0; itemIndex < currentSize; ++itemIndex)
                {
                    var menuItem = GetMenuItem(overAllItemIndex);
                    menuItem.IsExpandable = m_groupsExpandable[i];

                    m_children.Add(menuItem);
                    ++overAllItemIndex;
                }
            }

            if (lastMenuGroupIndex >= 0)
            {
                m_children[lastMenuGroupIndex].JustAdded = true;
            }
        }

        private List<FrameworkElement> GetListBoxItemsInRange(int skip, int take)
        {
            var items = m_list.Items
                .Cast<object>()
                .Skip(skip)
                .Take(take)
                .Select(_x => m_list.ItemContainerGenerator.ContainerFromItem(_x) as FrameworkElement)
                .ToList();
            return items;
        }

        private List<FrameworkElement> ChildStackPanelsFor(List<FrameworkElement> parentItems)
        {
            var controls = parentItems.Select(_x => FindChildControl<StackPanel>(_x as DependencyObject, ControlToAnimate) as FrameworkElement).ToList();
            return controls;
        }

        public void CollapseAndClearAll()
        {
            var items = GetListBoxItemsInRange(0, m_list.Items.Count);
            var controls = ChildStackPanelsFor(items);

            m_slideOutStoryboardRunner.AllCompleted += OnClearAllAnimsComplete;

            m_fadeOutStoryboardRunner.Begin(controls);
            m_slideOutStoryboardRunner.Begin(items);

            m_children.Clear();
        }

        private void OnClearAllAnimsComplete()
        {
            ResetData();

            m_list.DataContext = null;
            m_list.ItemsSource = null;

            m_slideOutStoryboardRunner.AllCompleted -= OnClearAllAnimsComplete;
        }

        private DependencyObject FindChildControl<T>(DependencyObject control, string name)
        {
            var numChildren = VisualTreeHelper.GetChildrenCount(control);

            for (var i = 0; i < numChildren; i++)
            {
                DependencyObject child = VisualTreeHelper.GetChild(control, i);
                FrameworkElement element = child as FrameworkElement;
                
                // Not a framework element or is null
                if (element == null) return null;

                if (child is T && element.Name == name)
                {
                    // Found the control so return
                    return child;
                }
                else
                {
                    // Not found it - search children
                    DependencyObject nextLevel = FindChildControl<T>(child, name);

                    if (nextLevel != null)
                        return nextLevel;
                }
            }
            return null;
        }

        public void UpdateAndAnimateSources(
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren)
        {
            bool anySizeChanges = false;

            // Check each group to see if it has changed in size.
            for (int i = 0; i < m_groups.Count; i++)
            {
                int groupIndex = i;
                string groupName = m_groups[groupIndex];
                int currentSize = m_groupToChildrenMap[groupName].Count;

                if (!groupToChildren.ContainsKey(groupName))
                {
                    throw new ArgumentException("New data source missing group '" + groupName + "'. Cannot animate sizes!");
                }
                int targetSize = groupToChildren[groupName].Count;

                if (currentSize == targetSize)
                {
                    continue;
                }

                anySizeChanges = true;

                // If contracting, update sources at the end of the animation, otherwise update it at the beginning.
                if (targetSize < currentSize)
                {
                    int groupStart = GetViewIndexForGroupIndex(groupIndex);

                    var listener = new MenuDelayedSourceUpdateAnimatorListener(groups, groupsExpandable, groupToChildren, this);
                    m_fadeOutStoryboardRunner.AllCompleted += listener.OnCompleted;

                    var items = GetListBoxItemsInRange(groupStart + targetSize, currentSize - targetSize);
                    var controls = ChildStackPanelsFor(items);

                    m_slideOutStoryboardRunner.Begin(items);
                    m_fadeOutStoryboardRunner.Begin(controls);                    
                }
                else
                {
                    UpdateSources(groups, groupsExpandable, groupToChildren);
                    ForceSetAnimatedSizes();
                    NotifyDataSetChanged();

                    m_list.UpdateLayout();
                    int groupStart = GetViewIndexForGroupIndex(groupIndex);

                    var items = GetListBoxItemsInRange(groupStart + currentSize, targetSize - currentSize);
                    var controls = ChildStackPanelsFor(items);

                    m_slideInStoryboardRunner.Begin(items);
                    m_fadeInStoryboardRunner.Begin(controls);                    
                }
            }

            // If there were no size changes, don't animate anything and just refresh the data sources.
            if (!anySizeChanges)
            {
                UpdateSources(groups, groupsExpandable, groupToChildren);
                ForceSetAnimatedSizes();
                NotifyDataSetChanged();
            }
        }

        public int GetCount()
        {
            int count = 0;
            for (int groupIndex = 0; groupIndex < m_groups.Count; groupIndex++)
            {
                string key = m_groups[groupIndex];
                count += m_animatedSizesMap[key];
            }
            return count;
        }

        public object GetItem(int index)
        {
            int count = 0;
            for (int groupIndex = 0; groupIndex < m_groups.Count; groupIndex++)
            {
                string groupName = m_groups[groupIndex];
                List<string> children = m_groupToChildrenMap[groupName];
                if (children.Count == 0)
                {
                    continue;
                }

                for (int childIndex = 0; childIndex < m_animatedSizesMap[groupName]; childIndex++)
                {
                    if (count == index)
                    {
                        return children[childIndex];
                    }

                    count++;
                }
            }
            return "";
        }
        public long GetItemId(int index)
        {
            return index;
        }
        public int GetSectionIndex(int index)
        {
            int count = 0;
            for (int groupIndex = 0; groupIndex < m_groups.Count; groupIndex++)
            {
                string groupName = m_groups[groupIndex];
                List<string> children = m_groupToChildrenMap[groupName];
                for (int childIndex = 0; childIndex < children.Count; ++childIndex)
                {
                    if (count == index)
                    {
                        return groupIndex;
                    }
                    count++;
                }
            }
            return -1;
        }

        public int GetItemIndex(int index)
        {
            int count = 0;
            for (int groupIndex = 0; groupIndex < m_groups.Count; groupIndex++)
            {
                string groupName = m_groups[groupIndex];
                List<string> children = m_groupToChildrenMap[groupName];
                for (int childIndex = 0; childIndex < children.Count; ++childIndex)
                {
                    if (count == index)
                    {
                        return childIndex;
                    }
                    count++;
                }
            }
            return -1;
        }

        private bool IsHeader(int index)
        {
            int groupIndex = GetGroupIndexForViewIndex(index);
            int placeInGroup = GetPlaceInGroup(index);

            if (!m_groupsExpandable[groupIndex])
            {
                return true;
            }
            return placeInGroup == 0;
        }

        public MenuListItem GetMenuItem(int index)
        {
            string json = (string)GetItem(index);
            bool isHeader = IsHeader(index);
            int groupIndex = GetGroupIndexForViewIndex(index);
            string groupName = m_groups[groupIndex];
            int groupStartIndex = GetViewIndexForGroupIndex(groupIndex);
            int totalItemCount = m_animatedSizesMap.Values.Sum();
            bool isExpanded = isHeader && m_animatedSizesMap[groupName] > 1;

            if (isHeader)
            {
                return new MenuListItem(json, isExpanded, totalItemCount - index);
            }
            else
            {
                return new SubMenuListItem(json, totalItemCount - index);
            }
        }

        private int GetViewIndexForGroupIndex(int index)
        {
            int accumulatedGroupSize = 0;

            for (int groupIndex = 0; groupIndex < index; groupIndex++)
            {
                string groupName = m_groups[groupIndex];
                int groupSize = m_animatedSizesMap[groupName];
                accumulatedGroupSize += groupSize;
            }

            return accumulatedGroupSize;
        }

        private int GetGroupIndexForViewIndex(int index)
        {
            int count = 0;
            for (int groupIndex = 0; groupIndex < m_groups.Count; groupIndex++)
            {
                string groupName = m_groups[groupIndex];
                for (int childIndex = 0; childIndex < m_animatedSizesMap[groupName]; childIndex++)
                {
                    if (count == index)
                    {
                        return groupIndex;
                    }
                    count++;
                }
            }
            return -1;
        }

        public int GetPlaceInGroup(int index)
        {
            int count = 0;
            for (int groupIndex = 0; groupIndex < m_groups.Count; groupIndex++)
            {
                string groupName = m_groups[groupIndex];
                for (int childIndex = 0; childIndex < m_animatedSizesMap[groupName]; childIndex++)
                {
                    if (count == index)
                    {
                        return childIndex;
                    }
                    count++;
                }
            }
            return 0;
        }

        private ObservableCollection<MenuListItem> m_children;

        public ObservableCollection<MenuListItem> Children
        {
            get
            {
                return m_children;
            }
        }
    }
}