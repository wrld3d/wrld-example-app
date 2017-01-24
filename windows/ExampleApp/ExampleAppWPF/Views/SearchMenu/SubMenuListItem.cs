using Newtonsoft.Json.Linq;
using System;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public class SubMenuListItem : MenuListItem
    {
        ImageSource m_icon;
        private string m_details;

        public string DetailVisibility { get; private set; } = "Collapsed";
        public SolidColorBrush TitleTextColor { get; private set; } = Colour.darkgrey;

        public ImageSource Icon
        {
            get { return m_icon; }
        }

        public string Details
        {
            get { return m_details; }
        }

        public SubMenuListItem(string json, int zIndex, bool isInKioskMode)
            : base(json, false, zIndex)
        {
            JObject parsed = JObject.Parse(json);
            JToken iconField;

            if (parsed.TryGetValue("icon", out iconField))
            {
                var iconName = iconField.Value<string>();
                m_icon = IconProvider.GetIconForTag(iconName, isInKioskMode);
            }

            JToken detailsField;
            if (parsed.TryGetValue("details", out detailsField))
            {
                m_details = detailsField.Value<string>();
                DetailVisibility = "Visible";
                TitleTextColor = Colour.black;
            }
        }
    }
}