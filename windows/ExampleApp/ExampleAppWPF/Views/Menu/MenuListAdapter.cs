using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Diagnostics;
using System.Collections;

namespace ExampleAppWPF
{
    public class MenuListAdapter
    {
        private List<string> m_groups;
        private List<bool> m_groupsExpandable;
        private Dictionary<string, List<string>> m_groupToChildrenMap;
        
        private Dictionary<string, int> m_animatedSizesMap;
        private bool m_shouldAlignIconRight;

        private StoryboardRunner m_itemShutterOpenStoryboardRunner;
        private StoryboardRunner m_itemShutterCloseStoryboardRunner;

        private StoryboardRunner m_slideInStoryboardRunner;
        private StoryboardRunner m_slideOutStoryboardRunner;

        private ListBox m_list;

        private readonly string ControlToAnimate;

        private ObservableCollection<MenuListItem> m_children;

        private bool m_isInKioskMode;

        public ObservableCollection<MenuListItem> Children
        {
            get
            {
                return m_children;
            }
        }


        public MenuListAdapter(bool shouldAlignIconRight, ListBox list,
            Storyboard slideInAnimation, Storyboard slideOutAnimation, Storyboard itemShutterOpenAnimation, Storyboard itemShutterCloseAnimation, string controlToAnimate, bool isInKioskMode)
        {   
            m_animatedSizesMap = new Dictionary<string, int>();

            m_groups = new List<string>();
            m_groupsExpandable = new List<bool>();
            m_groupToChildrenMap = new Dictionary<string, List<string>>();

            m_shouldAlignIconRight = shouldAlignIconRight;
            m_children = new ObservableCollection<MenuListItem>();

            m_list = list;

            m_itemShutterOpenStoryboardRunner = new StoryboardRunner(itemShutterOpenAnimation);
            m_itemShutterCloseStoryboardRunner = new StoryboardRunner(itemShutterCloseAnimation);

            m_slideInStoryboardRunner = new StoryboardRunner(slideInAnimation);
            m_slideOutStoryboardRunner = new StoryboardRunner(slideOutAnimation);

            ControlToAnimate = controlToAnimate;

            m_isInKioskMode = isInKioskMode;
        }

        public bool IsAnimating()
        {
            return m_itemShutterOpenStoryboardRunner.IsAnimating ||
                m_itemShutterCloseStoryboardRunner.IsAnimating ||
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

            m_list.DataContext = null;
            m_list.ItemsSource = null;

            m_list.UpdateLayout();
        }

        public void SetData(
            IEnumerable itemsSource,
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren)
        {
            if (m_list.ItemsSource != itemsSource)
            {
                ResetData();
                m_list.ItemsSource = itemsSource;
                AnimateItemsInShutterOnly(groups, groupsExpandable, groupToChildren, 0, m_list.Items.Count);
            }
            else
            {
            UpdateAndAnimateSources(groups, groupsExpandable, groupToChildren);
            }

            m_list.DataContext = this;
        }

        public void UpdateSources(
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren)
        {
            m_groups = groups;
            m_groupsExpandable = groupsExpandable;
            m_groupToChildrenMap = groupToChildren;

            ForceSetAnimatedSizes();
            NotifyDataSetChanged();
            m_list.UpdateLayout();
        }

        public Tuple<int, int> GetSectionAndChildIndicesFromSelection(int selectedIndex)
        {
            int sectionIndex = GetSectionIndex(selectedIndex);
            int childIndex = GetItemIndex(selectedIndex);
            return Tuple.Create(sectionIndex, childIndex);
        }

        public void CollapseAndClearAll()
        {
            SetData(m_list.ItemsSource, new List<string>(), new List<bool>(), new Dictionary<string, List<string>>());
        }

        private void ForceSetAnimatedSizes()
        {
            m_animatedSizesMap.Clear();
            for (int groupIndex = 0; groupIndex < m_groups.Count; groupIndex++)
            {
                var key = m_groups[groupIndex];
                m_animatedSizesMap[key] = m_groupToChildrenMap[key].Count;
            }
        }

        private void SetAnimatedGroupSize(string groupName, int size)
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
        private void NotifyDataSetChanged()
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

        public List<FrameworkElement> GetListBoxItemsInRange(int skip, int take)
        {
            var items = m_list.Items
                .Cast<object>()
                .Skip(skip)
                .Take(take)
                .Select(_x => m_list.ItemContainerGenerator.ContainerFromItem(_x) as FrameworkElement)
                .ToList();
            return items;
        }

        public List<FrameworkElement> ChildStackPanelsFor(List<FrameworkElement> parentItems)
        {
            var controls = parentItems.Where(_x => _x != null).Select(_x => FindChildControl<StackPanel>(_x as DependencyObject, ControlToAnimate) as FrameworkElement).ToList();
            return controls;
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

        private void UpdateAndAnimateSources(
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren)
        {
            if (m_groups.Count == groups.Count)
            {
                var currentChildCounts = CalcChildCountsForGroups(m_groupToChildrenMap);
                var newChildCounts = CalcChildCountsForGroups(groupToChildren);

                var numDifferences = 0;
                for (var groupIndex = 0; groupIndex < currentChildCounts.Count; groupIndex++)
                {
                    if (currentChildCounts[groupIndex] != newChildCounts[groupIndex])
                    {
                        numDifferences++;
                    }
                }

                if (numDifferences > 0)
                {
                    if (numDifferences == 1)
                    {
                        var groupIndex = IndexOfFirstDifference(currentChildCounts, newChildCounts);

                        var currentChildCount = currentChildCounts[groupIndex];
                        var newChildCount = newChildCounts[groupIndex];

                        var startIndex = CalcFirstChildIndex(groupIndex);
                        var itemCount = Math.Abs(newChildCount - currentChildCount);

                        var expanding = (newChildCount > currentChildCount);
                        if (expanding)
                        {
                            AnimateItemsIn(groups, groupsExpandable, groupToChildren, startIndex, itemCount);
                        }
                        else
                        {
                            AnimateItemsOut(groups, groupsExpandable, groupToChildren, startIndex, itemCount);
                        }
                    }
                    else
                    {
                        var outStartIndex = 0;
                        var outItemCount = 0;
                        var inGroupIndex = 0;
                        var inItemCount = 0;

                        for (var groupIndex = 0; groupIndex < currentChildCounts.Count; groupIndex++)
                        {
                            if (currentChildCounts[groupIndex] != newChildCounts[groupIndex])
                            {
                                var currentChildCount = currentChildCounts[groupIndex];
                                var newChildCount = newChildCounts[groupIndex];

                                var expanding = (newChildCount > currentChildCount);
                                if (expanding)
                                {
                                    inGroupIndex = groupIndex;
                                    inItemCount = Math.Abs(newChildCount - currentChildCount);
                                }
                                else
                                {
                                    outStartIndex = CalcFirstChildIndex(groupIndex);
                                    outItemCount = Math.Abs(newChildCount - currentChildCount);
                                }
                            }
                        }

                        AnimateItemsOutAndIn(groups, groupsExpandable, groupToChildren, outStartIndex, outItemCount, inGroupIndex, inItemCount);
                    }

                    return;
                }
                
                
            }

            if (groups.Count >= m_groups.Count)
            {
                AnimateItemsIn(groups, groupsExpandable, groupToChildren, m_groups.Count, groups.Count - m_groups.Count);
            }
            else
            {
                AnimateItemsOut(groups, groupsExpandable, groupToChildren, groups.Count, m_groups.Count - groups.Count);
            }

        }

        private List<int> CalcChildCountsForGroups(Dictionary<string, List<string>> groupToChildrenMap)
        {
            var childCounts = m_groups
                .Select(_key => groupToChildrenMap.ContainsKey(_key) ? groupToChildrenMap[_key].Count : 0)
                .ToList();
            return childCounts;
        }

        private int IndexOfFirstDifference(IList<int> a, IList<int> b)
        {
            Debug.Assert(a.Count == b.Count);
            for (var i = 0; i < a.Count; ++i)
            {
                if (a[i] != b[i])
                    return i;
            }
            return -1;
        }

        public int CalcFirstChildIndex(int groupIndex)
        {
            var elementIndexOfGroup = m_groups
                .Take(groupIndex)
                .Sum(_key => m_groupToChildrenMap[_key].Count);

            return elementIndexOfGroup + 1;
        }

        private void AnimateItemsIn(
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren,
            int startIndex,
            int itemCount)
        {
            UpdateSources(groups, groupsExpandable, groupToChildren);

            var itemsToAnimate = GetListBoxItemsInRange(startIndex, itemCount);

            if (itemsToAnimate.Any())
            {
                var controls = ChildStackPanelsFor(itemsToAnimate);

                m_slideInStoryboardRunner.Begin(itemsToAnimate);
                m_itemShutterOpenStoryboardRunner.Begin(controls);
            }
        }

        private void AnimateItemsOut(
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren,
            int startIndex,
            int itemCount)
        {
            m_list.UpdateLayout();
            var itemsToAnimate = GetListBoxItemsInRange(startIndex, itemCount);

            var parentGroupIndex = startIndex - 1;

            //animate out header for current group
            if (parentGroupIndex >= 0 && parentGroupIndex < m_children.Count)
            {
                m_children[parentGroupIndex].IsExpanded = false;
            }

            if (itemsToAnimate.Any())
            {
                var menuDelayedSourceUpdateAnimatorListener = new MenuDelayedSourceUpdateAnimatorListener(groups, groupsExpandable, groupToChildren, this);
                var controls = ChildStackPanelsFor(itemsToAnimate);
                m_slideOutStoryboardRunner.AllCompleted += menuDelayedSourceUpdateAnimatorListener.OnCompleted;
                m_slideOutStoryboardRunner.Begin(itemsToAnimate.Where(_x => _x != null).ToList());

                if (!m_itemShutterCloseStoryboardRunner.IsAnimating)
                {
                    m_itemShutterCloseStoryboardRunner.AllCompleted += ItemShutterCloseCompleted;
                    m_itemShutterCloseStoryboardRunner.Begin(controls);
                }
            }
        }

        private void ItemShutterCloseCompleted()
        {
            m_list.ItemsSource = null;
            m_itemShutterCloseStoryboardRunner.AllCompleted -= ItemShutterCloseCompleted;
        }

        private void AnimateItemsOutAndIn(
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren,
            int outStartIndex,
            int outItemCount,
            int inGroupIndex,
            int inItemCount)
        {
            m_list.UpdateLayout();
            var itemsToAnimate = GetListBoxItemsInRange(outStartIndex, outItemCount);

            var parentGroupIndex = outStartIndex - 1;
            
            if (parentGroupIndex >= 0 && parentGroupIndex < m_children.Count)
            {
                m_children[parentGroupIndex].IsExpanded = false;
            }

            if (itemsToAnimate.Any())
            {
                var menuDelayedSourceUpdateAnimatorListener = new MenuDelayedSourceUpdateAnimatorListener(groups, groupsExpandable, groupToChildren, this, inGroupIndex, inItemCount);
                var controls = ChildStackPanelsFor(itemsToAnimate);
                m_slideOutStoryboardRunner.AllCompleted += menuDelayedSourceUpdateAnimatorListener.OnCompleted;
                m_slideOutStoryboardRunner.Begin(itemsToAnimate);
                m_itemShutterCloseStoryboardRunner.Begin(controls);
            }
        }

        private void AnimateItemsInShutterOnly(
            List<string> groups,
            List<bool> groupsExpandable,
            Dictionary<string, List<string>> groupToChildren,
            int startIndex,
            int itemCount)
        {
            UpdateSources(groups, groupsExpandable, groupToChildren);

            var itemsToAnimate = GetListBoxItemsInRange(startIndex, itemCount);

            if (itemsToAnimate.Any())
            {
                var controls = ChildStackPanelsFor(itemsToAnimate);

                foreach (var item in itemsToAnimate)
                {
                    if(item != null)
                    {
                        var thickness = new Thickness(0, 0, 0, 0);
                        item.Margin = thickness;
                    }
                }

                m_itemShutterOpenStoryboardRunner.Begin(controls);
            }
        }


        private object GetItem(int index)
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

        private int GetSectionIndex(int index)
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

        private int GetItemIndex(int index)
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

        private MenuListItem GetMenuItem(int index)
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
                return new SubMenuListItem(json, totalItemCount - index, m_isInKioskMode);
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

        private int GetPlaceInGroup(int index)
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

        public StoryboardRunner GetSlideInStoryboardRunner()
        {
            return m_slideInStoryboardRunner;
        }

        public StoryboardRunner GetSlideOutStoryboardRunner()
        {
            return m_slideOutStoryboardRunner;
        }

        public StoryboardRunner GetItemShutterOpenStoryboardRunner()
        {
            return m_itemShutterOpenStoryboardRunner;
        }
    }
}
