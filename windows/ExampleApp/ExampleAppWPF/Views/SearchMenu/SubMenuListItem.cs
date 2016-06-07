using ExampleAppWPF.Views.SearchMenu;
using Newtonsoft.Json.Linq;
using System;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public class SubMenuListItem : MenuListItem
    {
        ImageSource m_icon;

        public ImageSource Icon
        {
            get { return m_icon; }
        }

        public SubMenuListItem(string json, int zIndex)
            : base(json, false, zIndex)
        {
            JObject parsed = JObject.Parse(json);
            JToken iconField;

            if (parsed.TryGetValue("icon", out iconField))
            {
                var iconCategoryName = iconField.Value<string>();
                m_icon = SearchMenuResultIconProvider.GetIconForCategory(iconCategoryName);
            }
        }
    }
}